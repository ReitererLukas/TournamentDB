#include "Handler.h"
#include "SharedMemory.h"
#include "db-definitions.h"
#include "FileSystemUtil.h"
#include <algorithm>
#include <assert.h>

Handler::Handler() {
  data_path_ = DATA_PATH;

  // init mutex locks
  structures_mutex_ = SharedMemory::getLock(HANDLER_LOCK_SHM);

  // init shared buffer
  shared_buffer_ = SharedMemory::getSharedBuffer();
}

Handler::~Handler() {
  SharedMemory::unmap(structures_mutex_, sizeof(std::mutex));
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