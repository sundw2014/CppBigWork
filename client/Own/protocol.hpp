#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

typedef struct
{
  char key[3];
  char cmd[16],value1[32],value2[32],value3[64];
  unsigned char length[4];
}Frame;

#define ROOMMAX 32
typedef struct
{
  unsigned int roomMax;
  char num[ROOMMAX];
}RoomTableInfo;

class Protocol {
private:

	int fd;
	fd_set fds;
	struct timeval tv;

	Frame sendingFrame;                           //the frame of the protocol
	void sendFrameReal();                       //send the frame prototype

public:
  Frame receivedFrame;
  //Constructor
	Protocol(int Protocol_fd);

	bool receiveFrame();

	//send the frame directly
    void sendFrame(const unsigned char lengths[],const char *cmd , const char *value1=NULL,const char *value2=NULL,const char *value3=NULL);

	bool available();

  bool isFrameValid(Frame &frame);
};

#endif
