#pragma once

#include <map>
#include "PageTable.h"

class SharedBuffer {
  void* address_;
  PageTable* page_table_; //

public:
  SharedBuffer(void* address);

  void* getAddress() { return address_; }
};