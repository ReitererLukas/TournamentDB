#include "CreateModel.h"

void CreateField::reset() {
  field_name_ = "";
  dt_ = Datatype::Type::INT;
  ranking_ = 0;
  is_pk_ = false;
}

CreateField::CreateField() {
  reset();
}