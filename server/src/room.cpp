#include "room.hpp"
#include "client.hpp"
#include "memory.h"
#include "protocol.hpp"
#include "updateDB.h"
#include "unistd.h"
#include "stdio.h"

Room::Room()
{
  memset(client , 0 , 2 * sizeof(Client *));
  state=false;
  numOfClients=0;
  turn=0;
}

Room::~Room()
{
  if(client[0]!=NULL)
    delete client[0];
  if(client[1]!=NULL)
    delete client[1];
}

int Room::addClient(Client &newClient)
{
  if(isFull())
    return -1;
  if(client[0]==NULL)
  {
    // printf("&client start\r\n");
    client[0]=&newClient;
    numOfClients = 1;
    // printf("client[0] = %x\r\n",client[0]);
  }
  else if(client[1]==NULL)
  {
    // printf("&client start\r\n");
    client[1]=&newClient;
    numOfClients = 2;
    // printf("client[1] = %x\r\n",client[1]);
  }
  return 0;
}
bool Room::isFull()
{
    if((client[0]==NULL) || (client[1]==NULL))
      return false;
    return true;
}

unsigned char Room::GameControl()
{
    //printf("GameControl in\r\n");
    //printf("clientPointer = %x\n\r",client[0]);
    client[0]->getClientInfoDB();

    //printf("updateDB1 ok\r\n");
    client[1]->getClientInfoDB();
    //printf("updateDB2 ok\r\n");
    unsigned char temp[4] = {5,0,0,0};
    client[0]->sendFrame(temp,"START");
    client[1]->sendFrame(temp,"START");
    printf("send start ok\r\n");
    while(1)
    {
        unsigned short times = 0;
        while(1)
        {
          sleep(5);
          times++;
          if(client[turn]->updateFrame())
          {
            if(client[turn]->frame.cmd == string("NEWINP"))
            {
                client[1-turn]->sendFrame(client[turn]->receivedFrame);
                break;
            }
            if(client[turn]->frame.cmd == string("ILOSE"))
            {
                client[turn]->score--;
                client[1-turn]->score++;
                client[0]->clientUpdateDB();
                client[1]->clientUpdateDB();
                return turn;//返回0或1说明返回值对应的人输了
            }
            if(client[turn]->frame.cmd == string("NOWINNER"))
                return 2;//平局不更新数据库
          }
          if(times>1800)   //三分钟 = 180秒 = 1800 * 100 * ms
          {
            unsigned char temp[4] = {3,0,0,0};
            client[1-turn]->sendFrame(temp,"ESC");
            client[turn]->score -= 2;
            client[turn]->clientUpdateDB();
            return turn+5;//返回5或6说明有人逃跑
          }
          usleep(100000);//延时一百毫秒
        }
        turn = (++turn) % 2;
    }
}
