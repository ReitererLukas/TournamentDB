#pragma once

#include "vector"
#include "BaseCommand.h"

class CommandRunner {
  std::vector<BaseCommand*> commands_;

public:
  bool executeCommand(std::string& cmd);
  void test();
  void commandLoop(int socket_descriptor);


  // Singleton logic
public:
  CommandRunner(CommandRunner &other) = delete;
  void operator=(const CommandRunner&) = delete;
  static CommandRunner *instance();

private:

  static CommandRunner* instance_;
  CommandRunner();
  ~CommandRunner();
};