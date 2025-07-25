#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <mutex>
#include "CommandRunner.h"
#include "SharedMemory.h"
#include "db-definitions.h"
#include "BufferBlock.h"
#include "SharedBuffer.h"

#define PORT 9876

void resetSHMObjects();

// https://github.com/bozkurthan/Simple-TCP-Server-Client-CPP-Example/blob/master/tcp-Server.cpp
int main() {
  resetSHMObjects();
  std::cout << "Starting DB" << std::endl;
  CommandRunner::instance()->test();

    
  //setup a socket and connection tools
  sockaddr_in servAddr;
  memset(&servAddr, 0, sizeof(sockaddr_in));

  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(PORT);
 
  //open stream oriented socket with internet address
  //also keep track of the socket descriptor
  int serverSd = socket(AF_INET, SOCK_STREAM, 0);
  if(serverSd != 0) {
    std::cerr << "Error establishing the server socket" << std::endl;
    exit(0);
  }

    //bind the socket to its local address
  int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, sizeof(servAddr));
  if (bindStatus != 0) {
    std::cerr << "Error binding socket to local address" << std::endl;
    exit(0);
  }


  //listen for up to 5 requests at a time
  listen(serverSd, 5);

  while(1) {

    //receive a request from client using accept
    //we need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    //accept, create a new socket descriptor to 
    //handle the new connection with client
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    
    pid_t pid = fork();
    if (pid == 0) {
      close(serverSd);
      CommandRunner::instance()->commandLoop(newSd);
      close(newSd);
      exit(0);
    }
    close(newSd);
  }
  close(serverSd);
  return 0; 
}

void resetSHMObjects() {
  memset((void*)SharedMemory::getLockFileMapped(), 0, sizeof(std::mutex) * Locks::number_of_locks());

  // TODO: for now clearing is fine. But what would be best if the db doesn't shut down gracefully?
  // maybe we then want to recover the data in the shared buffer that wasn't written to the files yet?
  memset(SharedMemory::getPageTable(), 0, sizeof(PageTableKey) * SHARED_BUFFER_SLOTS);
  memset(SharedMemory::getSharedBuffer()->getAddress(), 0, sizeof(BufferBlock) * SHARED_BUFFER_SLOTS);
}