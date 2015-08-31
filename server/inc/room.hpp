#ifndef _ROOM_H_
#define _ROOM_H_

#include "client.hpp"

class Room
{
private:
  Client *client[2];
  bool state;
  unsigned char numOfClients;
public:
  Room();
  ~Room();
  bool isFull();
  int addClient(Client &newClient);
  bool isPlaying(){return state;}
  unsigned char GetNumOfClients(){return numOfClients;}
};

#endif
