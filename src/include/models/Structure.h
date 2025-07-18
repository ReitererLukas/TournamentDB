#pragma once

#include "db-definitions.h"
#include "types.h"
#include "Array.h"

struct FieldDescription {
  const char field_name[MAX_NAME_LENGTH];
  const Datatype::Type dt_;
  const int ranking_;
  const bool is_pk_;
};

typedef Array<FieldDescription> StructureType;


