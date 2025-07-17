#pragma once

#include "BaseModel.h"
#include "types.h"

struct InsertField {
  std::string field_name_;
  std::string value;

  InsertField();

  void reset();
};

struct InsertParamters : public BaseParamContainer {
  Structure::Type type_;
  std::string structure_name_;
  std::string home_pk_;
  std::vector<InsertField> home_fields_;
  // std::string guest_pk_;
  // std::vector<InsertField> guest_fields_;
};

