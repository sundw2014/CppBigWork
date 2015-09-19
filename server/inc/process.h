#ifndef _PROCESS_H_
#define _PROCESS_H_
#include "hall.hpp"
#include <arpa/inet.h>
typedef struct
{
	struct sockaddr_in client_addr;
	unsigned int client_addr_len;
	int fd;
}ClientArg;
void *ClientProcess(void *shareClientArg);

typedef struct
{
    Room *room;
}GameArg;
void *gameRunning(void *Arg);
#endif
