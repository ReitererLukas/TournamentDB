#include "CommandRunner.h"
#include <wait.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "CreateCommand.h"
#include "StringUtil.h"

#define BUFFER_SIZE 1024 * 32

CommandRunner::CommandRunner() {
  commands_.push_back(new CreateCommand("CREATE"));
}

CommandRunner::~CommandRunner() {
  for(BaseCommand* command : commands_) {
    delete command;
  }
}


void CommandRunner::test() {
  std::string input = "CREATE LIGA test(f1{INT,0,pk})";
  if(executeCommand(input)) {
    std::cout << "OK" << std::endl;
  } else {
    std::cout << "NOK" << std::endl;
  }
  exit(0);
}


bool CommandRunner::executeCommand(std::string& cmd) {
  std::vector<std::string> params = StringUtil::splitString(cmd, " ");

  if(params.empty()) {
    return false;
  }

  for(BaseCommand* command : commands_) {
    if(command->getName() == params.at(0)) {
      return command->executeCommand(params);
    }
  }

  return false;
}

void CommandRunner::commandLoop(int socket_descriptor) {
  while(1) {
    char message[BUFFER_SIZE];
    memset(message, 0, BUFFER_SIZE);
    //receive a message from the client (listen)
      
    int ret = recv(socket_descriptor, message, BUFFER_SIZE, 0);

    if(ret == 0) {
      std::cout << "Client disconnected" << std::endl;
      break;
    }

    std::string cmd = std::string(message);
    bool ok = executeCommand(cmd);

    if(ok) {
      send(socket_descriptor, "OK\0", 3, 0);
    } else {
      send(socket_descriptor, "NOK\0", 4, 0);
    }
  }
}


// Singleton logic
CommandRunner* CommandRunner::instance_ = nullptr;

CommandRunner* CommandRunner::instance() {
  if(instance_ == nullptr) {
    instance_ = new CommandRunner();
  }
  return instance_;
}



