#ifndef _MTYPE_H_
#define _MTYPE_H_
#include "memory.h"

class ChessBoard;
typedef unsigned int uint32;
typedef short int16;
typedef unsigned char uint8;
typedef struct _ZobristNode{
  uint32 hash;
  int16 value;
  bool operator !(){
      if(hash == 0)
          return true;
      return false;
  }
  bool operator ==(const struct _ZobristNode &rhs){
      if(rhs.hash==hash)
          return true;
      return false;
  }
  //use the default constructor
}ZobristNode;

class BitBoard{
#define SIZE 32
private:
  uint8 board[SIZE];
public:
  BitBoard()
  {
      memset(board,0,SIZE);
  }
  BitBoard(const uint8 *b)
  {
      memcpy(board , b , SIZE);
  }
  //返回棋盘上i行j列有无子
  uint8 operator ()(uint8 i,uint8 j) const
  {
    if((i>=16) || (j>=16))
        return -1;
    uint8 block = (i*16+j)/8,byteMask = (i*16+j)%8;
    if(board[block] & (1<<byteMask))
        return 1;
    else
        return 0;
  }
  uint8 &operator [](uint8 index)
  {
    if ((index >= SIZE) || (index < 0))
        return board[0];//此处返回什么?
    return board[index];
  }
  const uint8 &operator [](uint8 index) const
  {
    if ((index >= SIZE) || (index < 0))
        return board[0];//此处返回什么?
    return board[index];
  }
  BitBoard &operator =(const struct BitBoard &rhs)
  {
      for(uint8 i=0;i<SIZE;i++)
          board[i]=rhs[i];
      return *this;
  }
#undef SIZE
};

typedef struct
{
    uint8 inp;
    int16 value;
}ThreadReturn;

typedef struct
{
    const ChessBoard *parent;
    uint8 inp;
    uint8 qtid;
    uint32 hash;
}ThreadArgs;

#endif
