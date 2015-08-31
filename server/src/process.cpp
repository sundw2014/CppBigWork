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
#include "client.hpp"
#include "mysql.h"
#include "mysql_version.h"
#include "my_list.h"
#include "mysql_com.h"
#include "mysql_time.h"
#include "my_alloc.h"
#include "typelib.h"
#include <string>
#include "hall.hpp"
using namespace std;

extern Hall hall;

typedef struct
{
	struct sockaddr_in client_addr;
	unsigned int client_addr_len;
	int fd;
}ClientArg;

//登录处理
static int LogIn(string &uname,string &passwd)
{
  MYSQL mysql;
  string query;
  MYSQL_RES *result;
  mysql_init(&mysql);

  if (!mysql_real_connect(&mysql,"localhost", "root" , "9123" , "game" , 0 , NULL , 0))
  {//判断连接是否失败。
    printf("Failed to connect to database: Error: %s/n",  mysql_error(&mysql));
    return -1;
  }

  query="select * from user where username='" + uname + "'";
  if(mysql_real_query(&mysql, query.c_str(),query.length()))
    return 1;   //没有此用户
  if((result=mysql_store_result(&mysql))==NULL)
    return 1;   //没有此用户

  if(mysql_num_fields(result)!=1)
    return 2;   //多个同名用户

  MYSQL_ROW row = mysql_fetch_row(result);

  unsigned long *lengths=mysql_fetch_lengths(result);

  string code(row[3],lengths[3]);
  if(code==passwd)
    return 0; //登录成功
  else
    return 4; //密码错误
}

//注册处理
static int SignUp(string &uname,string &passwd)
{
  MYSQL mysql;
  string query;
  MYSQL_RES *result;
  mysql_init(&mysql);

  if (!mysql_real_connect(&mysql,"localhost", "root" , "9123" , "game" , 0 , NULL , 0))
  {//判断连接是否失败。
    printf("Failed to connect to database: Error: %s/n",  mysql_error(&mysql));
    return -1;
  }

  query="select * from user where username='" + uname + "'";
  mysql_real_query(&mysql, query.c_str(),query.length());

  if((result=mysql_store_result(&mysql))==NULL)
  {
    query="insert into user (username,password) values ('"+uname+"','"+passwd;
    if(mysql_real_query(&mysql, query.c_str(),query.length()))
      return 1;
    else
      return 0;
  }
}

void *ClientProcess(void *shareClientArg)
{
  ClientArg *locArg = new ClientArg;
  //建立堆变量存储socket，释放
  memcpy(locArg,shareClientArg,sizeof(ClientArg));
  memset(&shareClientArg,0,sizeof(ClientArg));
  ((ClientArg *)shareClientArg)->fd=-1;
  //子线程分离
  pthread_detach(pthread_self());
  Client *client = new Client(locArg->fd,locArg->client_addr,locArg->client_addr_len);//当一个socket和client对象绑定之后socket回收有client析构时完成
  delete locArg;locArg=NULL;
  if(!client->updateFrame())
  {//死连接,线程自杀.
    delete client;
    return NULL;
  }

  //登录start
  if(client->frame.cmd==string("LOGIN"))
  {
    if(LogIn(client->frame.value1,client->frame.value3)!=0)
    {
      unsigned char temp[4]={6,0,0,0};
      client->sendFrame(temp,"ERROR");
      //登录失败,具体原因根据返回值,线程自杀.
      delete client;
      return NULL;
    }
    //登录成功，返回房间列表
    RoomTableInfo tempInf=hall.GetHallInfo();
    unsigned char temp[4]={11,0,0,sizeof(RoomTableInfo)};
    client->sendFrame(temp,"SUCCESSFUL",NULL,NULL,(char *)&tempInf);
    unsigned times=0;

  while(1)
  {
    while(1)
    {
      if(times>200)
      {////十分钟不选房间则切断连接,线程自杀.
        unsigned char temp[4]={6,0,0,0};
        client->sendFrame(temp,"OUTOFTIME");
        delete client;
        return NULL;
      }

      if(client->updateFrame())//3秒
        if(client->frame.cmd == string("JOININ"))
          break;
      times++;
    }
    if(hall.joinRoom(atoi(client->frame.value1.c_str()),*client))
      return NULL;
  }
}
//登录end

//注册start
if(client->frame.cmd==string("SIGNUP"))
{
  if(SignUp(client->frame.value1,client->frame.value3)!=0)
  {
    unsigned char temp[4]={6,0,0,0};
    client->sendFrame(temp,"ERROR");
    //登录失败,具体原因根据返回值,线程自杀.
    delete client;
    return NULL;
  }
  unsigned char temp[4]={3,0,0,0};
  client->sendFrame(temp,"OK");
  //登录失败,具体原因根据返回值,线程自杀.
  delete client;
  return NULL;
}
//注册end
  //非登录或连接
  delete client;
  return NULL;
}
