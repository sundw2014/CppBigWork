#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <sys/socket.h>
#include "protocol.hpp"
#include <netinet/in.h>
#include "mysql.h"
#include "mysql_version.h"
#include "my_list.h"
#include "mysql_com.h"
#include "mysql_time.h"
#include "my_alloc.h"
#include "client.hpp"

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
  std::string userName;
public:
  const Frame *receivedFrame;
  cFrame frame;
  Client(int fd,struct sockaddr_in &Tclient_addr,unsigned int &Tclient_addr_len);
  ~Client();
  bool updateFrame();
  bool sendFrame(const unsigned char lengths[],const char *cmd ,const char *value1=NULL,const char *value2=NULL,const char *value3=NULL);
  bool sendFrame(const Frame* frame);
  int score=0;
  unsigned char clientUpdateDB();
  unsigned char getClientInfoDB();
  void setUserName(const string &name)
  {userName=name;}
};

#endif
