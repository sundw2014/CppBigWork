#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <sys/socket.h>
#include "protocol.hpp"
#include <netinet/in.h>

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
  unsigned long userID;
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
