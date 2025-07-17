#include "PageTable.h"

#include <assert.h>

#include "SharedMemory.h"


BasicPageTable::BasicPageTable() {
  table_ = SharedMemory::getPageTable();
}

size_t BasicPageTable::getSlot(PageTableKey key) {
  size_t counter = 0;
  size_t org_hash = hashFunction(key);
  size_t current_hash = 0;
  do {
    current_hash = (org_hash + counter) % SHARED_BUFFER_SLOTS;
    counter++;
  } while(table_[current_hash] != key && counter <= SHARED_BUFFER_SLOTS && (table_[current_hash].valid_ || table_[current_hash].deleted_));

  if(!table_[current_hash].valid_ && !table_[current_hash].deleted_) {
    // we found empty place which was not deletd => not in map
    return newSlot(key, current_hash);
  }

  if(counter > SHARED_BUFFER_SLOTS) {
    assert(false);
    // TODO: evict data and place into evicted slot
  }

  return current_hash;
}

size_t BasicPageTable::newSlot(PageTableKey key, size_t new_slot) {
  if(new_slot >= SHARED_BUFFER_SLOTS || table_[new_slot].valid_) {
    return -1;
  }

  key.valid_ = true;
  key.deleted_ = false;
  key.dirty_ = false;
  table_[new_slot] = key;

  return new_slot;
}

// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
size_t BasicPageTable::hashFunction(PageTableKey& key) {
  char *address = (char *) &key.file_block_;

  size_t hash = FNV_OFFSET_BASIS; // init start value
  for (size_t i = 0; i < 2 * sizeof(size_t); i++) {
    hash ^= address[i];        // XOR byte
    hash = hash * FNV_PRIME;         // Multiply hash by prime
  }
  return hash % SHARED_BUFFER_SLOTS;
}