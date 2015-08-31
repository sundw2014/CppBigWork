#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <arpa/inet.h>
#include "process.h"
#include "hall.hpp"
#include <signal.h>

typedef struct
{
	struct sockaddr_in client_addr;
	unsigned int client_addr_len;
	int fd;
}ClientArg;
static void ctrlCHandler(int)
{
	//关闭所有子线程并提示用户服务器即将停止服务
	exit(0);
}

Hall hall;

int main(void)
{
  signal(SIGINT , ctrlCHandler);

	pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t));
	unsigned int tidCNT=1,tidCurIndex=0;

/*begin:建立监听socket*/
  int listenfd,currentfd;
	struct sockaddr_in local_addr;

	if((listenfd = socket(AF_INET , SOCK_STREAM , 0)) == -1)
	{
		printf("create listen socket error: %s(error %d)\r\n",strerror(errno),errno);
		exit(0);
	}

	memset(&local_addr,0,sizeof(sockaddr_in));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	local_addr.sin_port = htons(10086);

	if((bind(listenfd , (struct sockaddr *)&local_addr , sizeof(local_addr))) == -1)
	{
		printf("bind socket error: %s(error %d)\r\n",strerror(errno),errno);
		exit(0);
	}

	if((listen(listenfd , 5)) == -1)
	{
		printf("listen socket error: %s(error %d)\r\n",strerror(errno),errno);
		exit(0);
	}
  /*end:建立监听socket*/


	printf("wait for client's request...\r\n");

	ClientArg shareClientArg;

  //阻塞，持续等待客户端连接请求，并建立处理线程
  for(;;)
  {
		if(shareClientArg.fd!=-1)
			continue;
		if((currentfd = accept(listenfd , (struct sockaddr *)&(shareClientArg.client_addr) , &(shareClientArg.client_addr_len))) == -1)
    {
     	printf("accept socket error: %s(error %d)\r\n",strerror(errno),errno);
    }
		shareClientArg.fd = currentfd;
		pthread_create(tid + tidCurIndex , NULL , ClientProcess , &shareClientArg);
		tidCurIndex++;
		tidCNT++;
		tid = (pthread_t *)realloc(tid , tidCNT * sizeof (pthread_t));

    printf("create a connection with client: %s\r\n",inet_ntoa(shareClientArg.client_addr.sin_addr));
	  //fcntl(currentfd , F_SETFL , O_NONBLOCK);
  }
}
