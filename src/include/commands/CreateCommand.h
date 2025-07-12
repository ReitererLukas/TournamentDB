#pragma once

#include <string>
#include <vector>
#include "BaseCommand.h"
#include "BaseModel.h"
#include "CreateModel.h"

class CreateCommand : public BaseCommand {

public:
  CreateCommand(std::string name) : BaseCommand{name} {}

  virtual bool executeCommand(std::vector<std::string>& parameters) override;
  virtual bool parseParameters(std::vector<std::string>& parameters, BaseParamContainer* parameterContainer) override;

  ~CreateCommand() = default;
};