#pragma once

#include "BaseModel.h"
#include "types.h"

struct CreateField {
  std::string field_name_;
  Datatype::Type dt_;
  int ranking_;
  bool is_pk_;

  void reset();
};

struct CreateParamters : public BaseParamContainer {
  Structure::Type type_;
  std::string name_;
  std::vector<CreateField> fields_;
};

