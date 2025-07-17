#include "CreateCommand.h"
#include "StringUtil.h"
#include "Handler.h"
#include "CreateModel.h"
#include <iostream>
#include <algorithm>

bool CreateCommand::executeCommand(std::vector<std::string>& params) {
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

bool CreateCommand::areParametersValid(CreateParamters& container) {
  std::vector<std::string> names;
  for(auto const& field : container.fields_) {
    if(std::find(names.begin(), names.end(), field.field_name_) != names.end()) {
      return false; // duplicated field name
    }
    names.push_back(field.field_name_);
  }

  return true;
}

bool CreateCommand::parseParameters(std::vector<std::string>& params, BaseParamContainer* paramContainer) {
  if(params.size() < 3 || params.at(0) != name_) {
    return false;
  }

  CreateParamters* container = (CreateParamters*) paramContainer;
  container->type_ = Structure::getTypeFromString(params.at(1));
  // container->name_ = params.at(2);
  if(container->type_ == Structure::Type::INVALID) {
    return false;
  }

  if(params.size() > 2) {

    std::string concatedArguments;
    
    for(size_t i = 2; i < params.size(); i++) {
      concatedArguments = concatedArguments.append(params.at(i)).append(" ");
    }

    size_t position = 0;
    container->name_ = StringReader::extractWord(concatedArguments, position);

    // 0 = before first (
    // 1 = field_name
    // 2 = datatype
    // 3 = ranking
    // 4 = primary key
    // 5 = wait for next field
    // 6 = after )
    int step = 0;
    CreateField field;
    while(position < concatedArguments.length()) {
      char ch = concatedArguments.at(position);

      if(ch == ')') {
        if(step != 4)
        step = 6;
      } else if(step == 0) {
        if(ch == '(') {
          step = 1;
        } else if (ch != ' ') {
          return false;
        }
      } else if(step == 1) {
        field.field_name_ = StringReader::extractWord(concatedArguments, position);
        if(position >= concatedArguments.size() || concatedArguments.at(position) != '{') {
          return false;
        }
        step = 2;
      } else if(step == 2) {
        field.dt_ = Datatype::getTypeFromString(StringReader::extractWord(concatedArguments, position));
        if(field.dt_ == Datatype::Type::INVALID) {
          return false;
        }
        if(position >= concatedArguments.size()) {
          return false;
        }
        ch = concatedArguments.at(position);
        if(ch == ',') {
          step = 3;
        } else if(ch == '}') {
          step = 5;
          container->fields_.push_back(field);
          field.reset();
        } else {
          return false;
        }
      } else if(step == 3) {
        field.ranking_ = StringReader::extractInteger(concatedArguments, position);
        if(position >= concatedArguments.size()) {
          return false;
        }

        ch = concatedArguments.at(position);
        if(ch == ',') {
        } else if(ch == '}') {
          step = 5;
          container->fields_.push_back(field);
          field.reset();
        } else {
          return false;
        }
      } else if(step == 4) {
        std::string word = StringReader::extractWord(concatedArguments, position);
        if(word != "pk" || concatedArguments.at(position) != '}') {
          return false;
        }
        step = 5;
        field.is_pk_ = true;
        container->fields_.push_back(field);
        field.reset();
      } else if(step == 5) {
        if(!StringReader::waitForNextArgument(concatedArguments, position, ',') || position >= concatedArguments.size()) {
          return false;
        }
        ch = concatedArguments.at(position);
        if(ch == ')') {
          step = 6;
        } else {
          step = 1;
        }
      } else if(step == 6) {
        if(ch != ' ') return false;
      }

      position++;

    }
  }



  return true;
}

