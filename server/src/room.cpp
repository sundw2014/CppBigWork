#include "room.hpp"
#include "client.hpp"
#include "memory.h"

Room::Room()
{
  memset(client , 0 , 2 * sizeof(Client *));
  state=false;
  numOfClients=0;
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
    client[0]=&newClient;
  if(client[1]==NULL)
    client[1]=&newClient;
  return 0;
}
bool Room::isFull()
{
    if((client[0]==NULL) || (client[1]==NULL))
      return false;
    return true;
}
