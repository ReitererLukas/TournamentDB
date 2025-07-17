#include "InsertModel.h"

void InsertField::reset() {
  field_name_ = "";
  value = "";
}

InsertField::InsertField() {
  reset();
}