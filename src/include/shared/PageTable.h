#pragma once

#include "types.h"
#include "db-definitions.h"

#define FNV_OFFSET_BASIS 14695981039346656037ull
#define FNV_PRIME 1099511628211ull

struct PageTableKey {
  size_t structure_id_;
  size_t file_block_;
  bool valid_;
  bool deleted_;
  bool dirty_;
};

constexpr bool operator==(const PageTableKey& lhs, const PageTableKey& rhs) {
  return lhs.valid_ && rhs.valid_ && lhs.structure_id_ == rhs.structure_id_ && lhs.file_block_ == rhs.file_block_;
}

constexpr bool operator!=(const PageTableKey& lhs, const PageTableKey& rhs) {
  return !(lhs == rhs);
}
 

class PageTable {
public:
  virtual size_t getSlot(PageTableKey key) = 0;
  virtual size_t newSlot(PageTableKey key, size_t new_slot) = 0;
};


// very basic pagetable map
// own implementation of hash map
// evaluate how many hash misses/faults and improve
// TODO: periodically clear pagetable, to reset the deleted flag (otherwise bad for performance)
class BasicPageTable : public PageTable{
  PageTableKey* table_;

public:
  BasicPageTable();

  virtual size_t getSlot(PageTableKey key) override;
  virtual size_t newSlot(PageTableKey key, size_t new_slot) override;

private:
  size_t hashFunction(PageTableKey& key);
};
