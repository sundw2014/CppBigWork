#include "hall.hpp"
#include <stdlib.h>
#include "memory.h"
#include "process.h"
#include "stdio.h"

Hall::Hall()
{
  roomTable=new Room *[ROOMMAX];
  memset(roomTable,0,sizeof(Client *) * ROOMMAX);
}
Hall::~Hall()
{
  for(unsigned int cnt=0;cnt<ROOMMAX;cnt++)
    if(roomTable[cnt]!=NULL)
      delete roomTable[cnt];
}
int Hall::createNewRoom(unsigned int roomNo)
{
  if((roomNo>=ROOMMAX) && (roomTable[roomNo] != NULL))
    return -1;
  roomTable[roomNo] = new Room();
    return 0;
}

int Hall::joinRoom(unsigned int roomNo,Client &client)
{
  if(roomNo>=ROOMMAX)
    return -1;
  if(roomTable[roomNo]==NULL)//还没有这个房间,新建一个
    if(createNewRoom(roomNo) != 0)
      return -1;
  if(roomTable[roomNo]->isFull())
    return -1;

  // printf("add client...\r\n");
  roomTable[roomNo]->addClient(client);
  // printf("add OK...\r\n");

  if(roomTable[roomNo]->isFull())//人已经到位开始游戏，新建线程
  {
        pthread_t tid;

        GameArg *tempArg = new GameArg{roomTable[roomNo]};
        // printf("roomTable[roomNo] = %x\r\n",roomTable[roomNo]);
        // printf("roomTable[roomNo] = %x\r\n",tempArg->room);
        pthread_create(&tid , NULL , gameRunning , tempArg);
  }
  return 0;
}

RoomTableInfo Hall::GetHallInfo()
{
  unsigned char temp=1;
  RoomTableInfo info;

  memset(&info,0,sizeof(RoomTableInfo));
  info.roomMax=ROOMMAX;

  //遍历整个RoomTable,得到每个房间的人数
  for (unsigned int i=0;i<ROOMMAX;i++)
  {
      if(roomTable[i]==NULL)
        info.num[i]=0;
      else
        info.num[i]=roomTable[i]->GetNumOfClients();
  }
  return info;
}
