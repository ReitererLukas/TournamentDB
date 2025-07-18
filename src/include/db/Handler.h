#pragma once

#include <vector>
#include <mutex>

#include "types.h"
#include "BaseCommand.h"
#include "CreateModel.h"
#include "SharedBuffer.h"

class Handler {

public:
  bool createNewStructure(CreateParamters& params);

private:
  std::string data_path_;
  std::vector<std::string> available_structures_;


  // locking
  std::mutex* handler_lock_;
  
  SharedBuffer* shared_buffer_;

// Singleton logic
public:
  Handler(Handler &other) = delete;
  void operator=(const Handler&) = delete;
  static Handler *instance();

private:

  static Handler* instance_;
  Handler();
  ~Handler();
};