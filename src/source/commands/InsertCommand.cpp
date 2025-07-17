#include "InsertCommand.h"
#include "StringUtil.h"
#include "Handler.h"
#include "InsertModel.h"
#include <iostream>
#include <algorithm>

bool InsertCommand::executeCommand(std::vector<std::string>& params) {
  CreateParamters parametersContainer;
  if(!parseParameters(params, &parametersContainer)) {
    return false;
  }

  std::cout << (parametersContainer.type_ == Structure::Type::LIGA ? 1 : 0) << " " << parametersContainer.name_ << std::endl;
  for(auto const& field : parametersContainer.fields_) {
    std::cout << field.field_name_ << " " << (field.dt_ == Datatype::Type::INT ? 1 : 0) << " " << field.ranking_ << " " << field.is_pk_ << std::endl;
  }

  if(!areParametersValid(parametersContainer)) {
    return false;
  }


  return Handler::instance()->createNewStructure(parametersContainer);
}

bool InsertCommand::areParametersValid(CreateParamters& container) {
  std::vector<std::string> names;
  for(auto const& field : container.fields_) {
    if(std::find(names.begin(), names.end(), field.field_name_) != names.end()) {
      return false; // duplicated field name
    }
    names.push_back(field.field_name_);
  }

  return true;
}

bool InsertCommand::parseParameters(std::vector<std::string>& params, BaseParamContainer* paramContainer) {
  if(params.size() < 5 || params.at(0) != name_ || params.at(1) != "INTO" || params.at(4) != "FOR") {
    return false;
  }

  InsertParamters* container = (InsertParamters*) paramContainer;

  container->type_ = Structure::getTypeFromString(params.at(2));
  if(container->type_ == Structure::Type::INVALID) {
    return false;
  }

  container->structure_name_ = params.at(3);

  std::string concatedArguments;
  for(size_t i = 5; i < params.size(); i++) {
    concatedArguments = concatedArguments.append(params.at(i)).append(" ");
  }

  std::vector<std::string> home_away = StringUtil::splitString(concatedArguments, " AGAINST ");

  int c = 0;
  for(std::string side : home_away) {
    c++;
    if(c > 1) {
      break; // TODO: remove for away team later
    }

    size_t position = 0;
    container->home_pk_ = StringReader::extractWord(concatedArguments, position);

    // 0 = before first (
    // 1 = field_name
    // 2 = value
    // 3 = wait for next field
    // 4 = after )
    int step = 0;
    InsertField field;
    while(position < concatedArguments.length()) {
      char ch = concatedArguments.at(position);

      if(step == 0) {
        if(ch == '(') {
          step = 1;
        } else if (ch != ' ') {
          return false;
        }
      } else if(step == 1) {
        field.field_name_ = StringReader::extractWord(concatedArguments, position);
        if(position >= concatedArguments.size() || concatedArguments.at(position) != ':') {
          return false;
        }
        step = 2;
      } else if(step == 2) {
        field.value = StringReader::extractWord(concatedArguments, position);
        if(position >= concatedArguments.size()) {
          return false;
        }
        ch = concatedArguments.at(position);
        step = 3;
        if(ch == ')') {
          step = 4;
        }
      } else if(step == 3) {
        if(!StringReader::waitForNextArgument(concatedArguments, position)) {
          return false;
        }
        step = 1;
      } else if(step == 4) {
        if(ch != ' ') {
          return false;
        }
      }

      position++;

    }
  }



  return true;
}

