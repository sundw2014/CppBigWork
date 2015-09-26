#ifndef _CLIENT_H_
#define _CLIENT_H_
#include "WinSock2.h"
#include "protocol.hpp"

typedef struct
{
  string cmd,value1,value2,value3;
}cFrame;
class Client
{
private:
  int socketFd;
  struct sockaddr_in client_addr;
	unsigned int client_addr_len;
  Protocol protocol;
  bool parseFrame();
public:
  const Frame *receivedFrame;
  cFrame frame;
  Client(int fd);
  ~Client();
  bool updateFrame();
  bool sendFrame(const unsigned char lengths[],const char *cmd ,const char *value1=NULL,const char *value2=NULL,const char *value3=NULL);
};

#endif
