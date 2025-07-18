#include "SharedMemory.h"

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <assert.h>

#include "db-definitions.h"
#include "BufferBlock.h"

void SharedMemory::unmap(void* ptr, size_t length) {
  assert(munmap(ptr, length) == 0 && "unmap failed");
}

std::mutex* SharedMemory::getLock(Locks::Type lock_type) {
  int fd = open(MUTEXES_SHM, O_CREAT | O_RDWR, SHM_OPEN_MODE);
  ftruncate(fd, sizeof(std::mutex) * Locks::number_of_locks());
  void* lock = mmap(0, sizeof(std::mutex), PROT_READ | PROT_WRITE, MAP_SHARED, fd, sizeof(std::mutex) * static_cast<int>(lock_type));
  close(fd);

  if(lock == MAP_FAILED) {
    assert(false && "Lock init failed");
  }
  return (std::mutex*) lock;
}

void* SharedMemory::getLockFileMapped() {
  int fd = open(MUTEXES_SHM, O_CREAT | O_RDWR, SHM_OPEN_MODE);
  ftruncate(fd, sizeof(std::mutex) * Locks::number_of_locks());
  void* lock = mmap(0, sizeof(std::mutex) * Locks::number_of_locks(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd);

  if(lock == MAP_FAILED) {
    assert(false && "Lock init failed");
  }
  return lock;
}


SharedBuffer* SharedMemory::getSharedBuffer() {
  size_t shared_buffer_length = sizeof(BufferBlock) * SHARED_BUFFER_SLOTS;
  int fd = open(SHARED_BUFFER_SHM, O_CREAT | O_RDWR, SHM_OPEN_MODE);
  ftruncate(fd, shared_buffer_length);
  void* start_shared_memory = mmap(0, shared_buffer_length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd);
  
  if(start_shared_memory == MAP_FAILED) {
    assert(false && "Shared Buffer init failed");
  } 
  return new SharedBuffer(start_shared_memory);
}

PageTableKey* SharedMemory::getPageTable() {
  size_t page_table_length = sizeof(PageTableKey) * SHARED_BUFFER_SLOTS;
  int fd = open(PAGE_TABLE_SHM, O_CREAT | O_RDWR, SHM_OPEN_MODE);
  ftruncate(fd, page_table_length);
  void* page_table = mmap(0, page_table_length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd);

  if(page_table == MAP_FAILED) {
    assert(false && "Page Table init failed");
  }
  return (PageTableKey*) page_table;
}