#include <iostream>
#include <netinet/in.h>
#include <netdb.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 9876
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024 * 32

// https://github.com/bozkurthan/Simple-TCP-Server-Client-CPP-Example/blob/master/tcp-Client.cpp
int main() {
  //we need 2 things: ip address and port number, in that order
  //create a message buffer 
  //setup a socket and connection tools 
  struct hostent* host = gethostbyname(SERVER_IP); 
  sockaddr_in sendSockAddr;
  
  memset(&sendSockAddr, 0, sizeof(sendSockAddr)); 
  sendSockAddr.sin_family = AF_INET; 
  sendSockAddr.sin_addr.s_addr = 
  inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
  sendSockAddr.sin_port = htons(PORT);
  int clientSd = socket(AF_INET, SOCK_STREAM, 0);
  //try to connect...
  int status = connect(clientSd, (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
  if(status != 0) {
    std::cout<<"Error connecting to socket!"<<std::endl;
    return -1;
  }
  std::cout << "Connected to the server!" << std::endl;
  int bytesRead, bytesWritten = 0;
  struct timeval start1, end1;
  while(1)
  {
    char msg[BUFFER_SIZE]; 
    std::cout << ">";
    std::string data;
    std::getline(std::cin, data);
    memset(msg, 0, sizeof(msg));
    strcpy(msg, data.c_str());

    if(data == "exit") {
        break;
    }
    send(clientSd, msg, strlen(msg), 0);
    memset(msg, 0, BUFFER_SIZE);
    recv(clientSd, msg, sizeof(msg), 0);
  }
  close(clientSd);

  return 0;
}