#pragma once

#include <mutex>
#include <string>
#include <vector>
#include "SharedBuffer.h"
#include "PageTable.h"

struct SharedMemory {

  static void unmap(void* ptr, size_t length);
  static std::mutex* getLock(std::string file);
  static SharedBuffer* getSharedBuffer();
  static PageTableKey* getPageTable();


};
