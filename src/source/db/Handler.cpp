#include "Handler.h"
#include "SharedMemory.h"
#include "db-definitions.h"
#include "FileSystemUtil.h"
#include "Structure.h"
#include <algorithm>
#include <assert.h>
#include <string.h>

Handler::Handler() {
  data_path_ = DATA_PATH;

  // init mutex locks
  handler_lock_ = SharedMemory::getLock(Locks::Type::HANDLER);

  // init shared buffer
  shared_buffer_ = SharedMemory::getSharedBuffer();
}

Handler::~Handler() {
  SharedMemory::unmap(handler_lock_, sizeof(std::mutex));
}

bool Handler::createNewStructure(CreateParamters& params) {
  handler_lock_->lock();
  if(std::find(available_structures_.begin(), available_structures_.end(), params.name_) != available_structures_.end()) {
    handler_lock_->unlock();
    return false; // structure name already exists
  }

  
  std::string data_path = data_path_;
  data_path.append("/").append(params.name_);  
  
  if(!FileSystemUtil::createDirectory(data_path)) {
    handler_lock_->unlock();
    return false; // directory already exists
  }
  
  available_structures_.push_back(params.name_);
  handler_lock_->unlock();

  // create all the necessary files
  std::string structure_dp = data_path;
  FileSystemUtil::createFile(structure_dp.append("/structure"));
  std::string pk_dp = data_path; 
  FileSystemUtil::createFile(pk_dp.append("/pks"));
  // dp = data_path; 
  // FileSystemUtil::createFile(dp.append("/pctable"));
  // dp = data_path; 
  // FileSystemUtil::createFile(dp.append("/config"));

  // save structure
  size_t size_of_structure = sizeof(size_t) + sizeof(FieldDescription) * params.fields_.size();
  void* address = malloc(size_of_structure);
  StructureType* structure = new (address) StructureType(params.fields_.size());
  for(size_t index = 0; index < params.fields_.size(); index++) {
    CreateField& field = params.fields_.at(index);
    FieldDescription fieldDesc = structure->array_[index];
    memcpy((char*) fieldDesc.field_name, field.field_name_.c_str(), field.field_name_.size());
    memcpy((void*)&fieldDesc.dt_, &field.dt_, sizeof(Datatype::Type));
    memcpy((void*)&fieldDesc.ranking_, &field.ranking_, sizeof(int));
    memcpy((void*)&fieldDesc.is_pk_, &field.is_pk_, sizeof(bool));
  }
  
  std::ofstream out(structure_dp, std::ios::binary | std::ios::trunc);
  assert(out && "file has to be valid");
  out.write(reinterpret_cast<const char*>(&structure), size_of_structure);
  out.close();
  delete structure;

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