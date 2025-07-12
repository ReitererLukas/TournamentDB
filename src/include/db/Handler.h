#pragma once

#include <vector>
#include "types.h"
#include "BaseCommand.h"
#include "CreateModel.h"
#include <mutex>

class Handler {

public:
  bool createNewStructure(CreateParamters& params);

private:
  std::string data_path_;
  std::vector<std::string> available_structures_;


  // locking
  std::mutex* structures_mutex_;


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