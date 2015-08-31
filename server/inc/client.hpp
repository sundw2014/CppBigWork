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
  Client(int fd,struct sockaddr_in &Tclient_addr,unsigned int &Tclient_addr_len);
  ~Client();
  bool updateFrame();
  bool sendFrame(unsigned char lengths[],char *cmd ,char *value1=NULL,char *value2=NULL,char *value3=NULL);
};

#endif
