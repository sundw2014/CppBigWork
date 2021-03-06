#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <string>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

using namespace std;

typedef struct
{
  char key[3];
  char cmd[16],value1[32],value2[32],value3[64];
  unsigned char length[4];
}Frame;

class Protocol {
private:

	int fd;
	fd_set fds;
	struct timeval tv;
  char *pointer;
	Frame sendingFrame;                           //the frame of the protocol
	void sendFrameReal();                       //send the frame prototype

public:
  Frame receivedFrame;
  //Constructor
	Protocol(int Protocol_fd);

	bool receiveFrame();

	//send the frame directly
  void sendFrame(const unsigned char lengths[],const char *cmd , const char *value1=NULL,const char *value2=NULL,const char *value3=NULL);
  void sendFrame(const Frame* frame);

	bool available();

  bool isFrameValid(Frame &frame);
};

#endif
