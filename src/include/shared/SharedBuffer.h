#pragma once

#include <map>

class SharedBuffer {
  void* address_;
  std::map<size_t, size_t> basic_page_table_; //

public:
  SharedBuffer(void* address);

  void* getAddress() { return address_; }
};