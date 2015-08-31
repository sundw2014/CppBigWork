#include "hall.hpp"
#include <stdlib.h>
#include "memory.h"

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
  if(roomTable[roomNo]!=NULL)
    if(!createNewRoom(roomNo))
      return -1;
  if(roomTable[roomNo]->isFull())
    return -1;
  roomTable[roomNo]->addClient(client);
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
      info.num[i]=roomTable[i]->GetNumOfClients();
  return info;
}
