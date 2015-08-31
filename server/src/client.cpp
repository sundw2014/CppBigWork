#include "client.hpp"
#include "protocol.hpp"
#include "unistd.h"
using namespace std;

Client::Client(int fd,struct sockaddr_in &Tclient_addr,unsigned int &Tclient_addr_len):socketFd(fd),protocol(fd)
{
  receivedFrame=(const Frame *)&(protocol.receivedFrame);
  client_addr=Tclient_addr;
  client_addr_len=Tclient_addr_len;
};

Client::~Client()
{
  close(socketFd);
}

bool Client::updateFrame()
{
  bool result=false;
  if(protocol.receiveFrame())
  {
    parseFrame();
    return true;
  }
  for(unsigned i=0;i<2;i++)
  {
    sleep(1000);
    if(protocol.receiveFrame())
    {
        return true;
        parseFrame();
    }
  }
  return false;
}

bool Client::parseFrame()
{
  frame.cmd=string(protocol.receivedFrame.cmd,(size_t)protocol.receivedFrame.length[0]);
  frame.value1=string(protocol.receivedFrame.value1,(size_t)protocol.receivedFrame.length[1]);
  frame.value2=string(protocol.receivedFrame.value1,(size_t)protocol.receivedFrame.length[2]);
  frame.value3=string(protocol.receivedFrame.value1,(size_t)protocol.receivedFrame.length[3]);
  return true;//备用返回值
}

bool Client::sendFrame(unsigned char lengths[],char *cmd ,char *value1,char *value2,char *value3)
{
  protocol.sendFrame(lengths,cmd,value1,value2,value3);
}
