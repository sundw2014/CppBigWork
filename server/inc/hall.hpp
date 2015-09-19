#ifndef _HALL_H_
#define _HALL_H_
#define ROOMMAX 32
#include "room.hpp"
#include "client.hpp"

typedef struct
{
  unsigned int roomMax;
  char num[ROOMMAX];
}RoomTableInfo;

class Hall
{
private:
  Room **roomTable;
public:
  Hall();
  ~Hall();
  int createNewRoom(unsigned int roomNo);
  int joinRoom(unsigned int roomNo,Client &client);
  RoomTableInfo GetHallInfo();

  Room *getRoom(unsigned char index)
  {
    if(index >= ROOMMAX)
      return NULL;
    return roomTable[index];
  }
};

#endif
