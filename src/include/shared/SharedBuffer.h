#pragma once

#include <map>

class SharedBuffer {
  const void* shared_memory_start_;
  std::map<size_t, size_t> basic_page_table_; //

public:
  SharedBuffer(void* shared_memory_start);
};