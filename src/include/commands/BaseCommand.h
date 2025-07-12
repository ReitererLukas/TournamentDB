#pragma once

#include <string>
#include <vector>
#include "BaseModel.h"

class BaseCommand {
protected:
  std::string name_;

public:
  BaseCommand(std::string name) : name_{name} {}

  virtual bool executeCommand(std::vector<std::string>& parameters) = 0;
  virtual bool parseParameters(std::vector<std::string>& parameters, BaseParamContainer* parameterContainer) = 0;


  std::string& getName() {
    return name_;
  }

  virtual ~BaseCommand() = default;
};