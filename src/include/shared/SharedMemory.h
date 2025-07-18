#pragma once

#include <mutex>
#include <string>
#include <vector>
#include "SharedBuffer.h"
#include "PageTable.h"
#include "db-definitions.h"

struct SharedMemory {

  static void unmap(void* ptr, size_t length);
  static std::mutex* getLock(Locks::Type file);
  static void* getLockFileMapped();
  static SharedBuffer* getSharedBuffer();
  static PageTableKey* getPageTable();


};
