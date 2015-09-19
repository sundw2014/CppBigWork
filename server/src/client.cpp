#include "client.hpp"
#include "protocol.hpp"
#include "unistd.h"
#include "stdio.h"
#include <sstream>
#include <string>
#include "stdio.h"
#include <iostream>

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
    // printf("ok rec\r\n");
    parseFrame();
    return true;
  }
  for(unsigned i=0;i<2;i++)
  {
    sleep(1);
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
  // printf("length = {%d,%d,%d,%d}\r\n",protocol.receivedFrame.length[0],protocol.receivedFrame.length[1],protocol.receivedFrame.length[2],protocol.receivedFrame.length[3]);
  // printf("frameCmd = %s   ,length = %d\r\n",protocol.receivedFrame.cmd,(size_t)protocol.receivedFrame.length[0]);
  frame.cmd=string(protocol.receivedFrame.cmd,(size_t)protocol.receivedFrame.length[0]);
  // printf("frame.cmd = %s",frame.cmd.c_str());
  frame.value1=string(protocol.receivedFrame.value1,(size_t)protocol.receivedFrame.length[1]);
  frame.value2=string(protocol.receivedFrame.value2,(size_t)protocol.receivedFrame.length[2]);
  frame.value3=string(protocol.receivedFrame.value3,(size_t)protocol.receivedFrame.length[3]);
  return true;//备用返回值
}

bool Client::sendFrame(const unsigned char lengths[],const char *cmd ,const char *value1,const char *value2,const char *value3)
{
  protocol.sendFrame(lengths,cmd,value1,value2,value3);
  return true;
}

bool Client::sendFrame(const Frame* frame)
{
  protocol.sendFrame(frame);
  return true;
}

unsigned char Client::clientUpdateDB()
{
  printf("in updateDB");
  MYSQL mysql;
  string query;
  MYSQL_RES *result;
  mysql_init(&mysql);

  if (!mysql_real_connect(&mysql,"localhost", "root" , "913256" , "game" , 0 , NULL , 0))
  {//判断连接是否失败。
    printf("Failed to connect to database: Error: %s/n",  mysql_error(&mysql));
    return -1;
  }

  std::string strScore;
  stringstream converter;
//  converter<<score;

  query="update user set score=" +   converter.str() + " where username='" + userName + "'";
  cout<<query<<endl;
  do
  {
    result = mysql_store_result( &mysql );
    mysql_free_result(result);
  }while( !mysql_next_result( &mysql ) );

  if(mysql_real_query(&mysql, query.c_str(),query.length()))
  {
    printf("Failed to exec query : Error:%s",mysql_error(&mysql));
    return 1;   //没有此用户
  }

  do
  {
    result = mysql_store_result( &mysql );
    mysql_free_result(result);
  }while( !mysql_next_result( &mysql ) );

  return 0;
}

unsigned char Client::getClientInfoDB()
{
  MYSQL mysql;
  string query;
  MYSQL_RES *result;
  mysql_init(&mysql);

  if (!mysql_real_connect(&mysql,"localhost", "root" , "913256" , "game" , 0 , NULL , 0))
  {//判断连接是否失败。
    printf("Failed to connect to database: Error: %s/n",  mysql_error(&mysql));
    return -1;
  }

  query="select * from user where username='" + userName + "'";

  //清空结果集
  do
  {
    result = mysql_store_result( &mysql );
    mysql_free_result(result);
  }while( !mysql_next_result( &mysql ) );

  if(mysql_real_query(&mysql, query.c_str(),query.length()))
  {
    printf("Failed to exec query : Error:%s",mysql_error(&mysql));
    return 1;   //没有此用户
  }

  result=mysql_store_result(&mysql);

  // printf("rows = %d",mysql_num_rows(result));

  if(mysql_num_rows(result)!=1)
  {
      mysql_free_result(result);
      return 2;   //多个同名用户
  }

  MYSQL_ROW row = mysql_fetch_row(result);
//	printf("fetch row ok\r\n");
  unsigned long *lengths=mysql_fetch_lengths(result);

  stringstream converter;
  converter<<std::string(row[3],lengths[3]);
  converter>>score;
  cout<<score<<endl;
//	cout<<code<<"|"<<passwd<<"|"<<endl;
	mysql_free_result(result);
  return 0; //登录成功
}
