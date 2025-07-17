#pragma once

#include <string>
#include <vector>
#include "BaseCommand.h"
#include "BaseModel.h"
#include "CreateModel.h"

class InsertCommand : public BaseCommand {

public:
  InsertCommand(std::string name) : BaseCommand{name} {}

  virtual bool executeCommand(std::vector<std::string>& parameters) override;
  virtual bool parseParameters(std::vector<std::string>& parameters, BaseParamContainer* parameterContainer) override;

  virtual ~InsertCommand() = default;

private:
  bool areParametersValid(CreateParamters& container);
};