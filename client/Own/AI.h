#ifndef _AI_H_
#define _AI_H_

#include "Zobrist.h"
#include "mType.h"
#include "memory.h"
#include "vector"

#define BOARDSIZE 16
extern const uint8 maxDepth;
extern uint32 hash;
extern uint8 realPly;
extern std::vector<ZobristNode> *volatile hashValues[];
extern int numProcessors;
//博弈树上的每一个节点都是一个棋盘局面即ChessBoard
class ChessBoard{
private:
  //黑白棋盘最大限度减小内存占用,GNUGO
  BitBoard white,black;
  //该节点截止当前的最佳收益（或者称为 价值），父节点的估计收益的负值
  int16 value,parentValue;
  //此节点在当前搜索过程中所处的深度，根节点为0,到达最大深度时截止
  uint8 depth,input;
  //父节点的hash值主要用于生成当前节点的hash
  uint32 parentHash;

  bool win=false;
public:
  //返回该节点第i行，第j列的棋子，返回0,1,2，含义与ui相同
  uint8 operator ()(uint8 i,uint8 j);
  //这个构造是为了从ui中的棋盘类型生成ai中的位棋盘,在ui中调用
  ChessBoard(int a[16][16],uint32 hash);
  //传入父节点的估计值,父节点的深度,输入（即着子点),父节点的hash
  ChessBoard(const ChessBoard &parent,uint8 inp,uint32 oldHash);

  //~ChessBoard();

  //hash的计算,传入旧hash值，改变的位置，该位置的新值,旧值(0,1,2)
  uint32 ZobristHash(uint32 oldHash,uint8 pos , uint8 newState , uint8 oldState){
      //根据增量算出hash
      return (oldHash ^ (uint32)ZobristTable[pos][newState] ^ (uint32)ZobristTable[pos][oldState]);
  }

  //判断收益是否为有效值
  static bool isValueValid(int16 value){
    return ((-1001 < value) && (value < 1001))?true:false;
  }

  //会返回这个节点的评估值，当他被cutoff时会输出-100001,正常值在-1000到1000之间，
  //表示最底层节点MC中(胜的场数-输的场数,随机测1000场，允许平局，但尽量减少)
  int16 run();

  //蒙特卡罗方法，用于评估整个棋盘，在depth到达最大时调用
  int16 MC();
};

uint8 getValidPos(const BitBoard &table,const uint8 ran=1);
static void *SearchThe(void *inp);
#endif
