#include "mType.h"
#define ZobrisrtInitValue 0x4E53A23F
extern const uint32 ZobristTable[256][3];

//hash的计算,传入旧hash值，改变的位置，该位置的新值,旧值(0,1,2)
uint32 ZobristHash(uint32 oldHash,uint8 pos , uint8 newState , uint8 oldState);
