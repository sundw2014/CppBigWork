#include "protocol.hpp"
#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>

void Protocol::sendFrameReal()
{
  write(fd, &sendingFrame , sizeof(Frame));
}

Protocol::Protocol(int Protocol_fd)
{
  fd=Protocol_fd;
  //initiate the variables
  memset(&receivedFrame,0,sizeof(Frame));
  memset(&sendingFrame,0,sizeof(Frame));

  fcntl(fd , F_SETFL , O_NONBLOCK);
  FD_ZERO(&fds);
  FD_SET(fd , &fds);
  tv.tv_usec = 0;
}

bool Protocol::receiveFrame()
{
  char tempCh=NULL;
  char *tempP=(char *)&receivedFrame;
  //printf("select\r\n");
//  if (1){
	  //select(fd+1 , &fds , NULL , NULL ,&tv)>0) {
    //printf("start while\r\n");
  unsigned char cnt=0,size=sizeof(Frame);
  while ((cnt++ < size) && (read(fd , &tempCh , 1) == 1)){
      *(tempP++) = tempCh;
    //while(1);
    }
  return isFrameValid(receivedFrame);
  }

void Protocol::sendFrame(unsigned char lengths[],char *cmd ,char *value1,char *value2,char *value3)
{
  memset(&sendingFrame,0,sizeof(Frame));
  memset(&(sendingFrame.key),0xAD,3);
  memcpy(&(sendingFrame.cmd),cmd,lengths[0]);
  if(value1!=NULL)
    memcpy(&(sendingFrame.value1),value1,lengths[1]);
  if(value2!=NULL)
    memcpy(&(sendingFrame.value2),value2,lengths[2]);
  if(value3!=NULL)
    memcpy(&(sendingFrame.value3),value3,lengths[3]);
  for(unsigned char i=0;i<4;i++)
    sendingFrame.length[i] = lengths[i];
  sendFrameReal();
}

bool Protocol::available()
{

}

bool Protocol::isFrameValid(Frame &frame)
{
  for (unsigned char i=0;i<3;i++)
    if(frame.key[i]!=0xAD)
      return false;
  return true;
}
