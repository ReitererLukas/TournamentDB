#include "Handler.h"
#include "shared-memory.h"
#include "db-definitions.h"
#include "FileSystemUtil.h"
#include <algorithm>

Handler::Handler() {
  data_path_ = DATA_PATH;

  // init mutex locks
  int fd = shm_open(HANDLER_LOCK_SHM, O_CREAT | O_RDWR, SHM_OPEN_MODE);
  ftruncate(fd, sizeof(std::mutex));
  structures_mutex_ = (std::mutex*) mmap(0, sizeof(std::mutex), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
}

Handler::~Handler() {
  munmap(structures_mutex_, sizeof(std::mutex));
}

bool Handler::createNewStructure(CreateParamters& params) {
  structures_mutex_->lock();
  if(std::find(available_structures_.begin(), available_structures_.end(), params.name_) != available_structures_.end()) {
    structures_mutex_->unlock();
    return false; // structure name already exists
  }

  
  std::string data_path = data_path_;
  data_path.append("/").append(params.name_);  
  
  if(!FileSystemUtil::createDirectory(data_path)) {
    structures_mutex_->unlock();
    return false; // directory already exists
  }
  
  available_structures_.push_back(params.name_);
  structures_mutex_->unlock();

  // create all the necessary files
  std::string dp = data_path;
  FileSystemUtil::createFile(dp.append("/type"));
  dp = data_path; 
  FileSystemUtil::createFile(dp.append("/games"));
  dp = data_path; 
  FileSystemUtil::createFile(dp.append("/pctable"));
  dp = data_path; 
  FileSystemUtil::createFile(dp.append("/config"));


  return true;
}


// Singleton logic
Handler* Handler::instance_ = nullptr;

Handler* Handler::instance() {
  if(instance_ == nullptr) {
    instance_ = new Handler();
  }
  return instance_;
}