#include "AI.h"
#include<algorithm>
#include "mType.h"
#include "time.h"
#include <pthread.h>
#include <unistd.h>
#include "stdio.h"

uint32 hash = ZobrisrtInitValue;
//记录当前实际的层数，游戏之初设为0
//偶数层为白子max,1
uint8 realPly = 0;
//最大搜索深度
const uint8 maxDepth = 3;
const uint8 maxThreads = 12;
int numProcessors = 1;//cpu核心数
 std::vector<ZobristNode> *volatile hashValues[maxDepth+1];
pthread_mutex_t hashMymutex[maxDepth+1] = PTHREAD_MUTEX_INITIALIZER;
//互斥信号量定义成volatile,防缓存
volatile bool hashValuesLock[maxDepth+1],isThreadEnd[maxThreads],isTidRunning[maxThreads],isTidJoin[maxThreads];
pthread_t tid[maxThreads];

uint8 getPosValue(const BitBoard &board,uint8 pos)
{
    uint8 dim[2] = {pos / 16, pos % 16};
    uint8 tempCnt = 1,tempCnt0;

    //行检测
    uint8 i=1,j=1;
    tempCnt0 = 1;
    for(i=1;board(dim[0]+i,dim[1])==1;i++)
      tempCnt0++;
    for(i=1;board(dim[0]-i,dim[1])==1;i++)
      tempCnt0++;
    if(tempCnt0 >= 5)
        return 256;
    tempCnt += tempCnt0;

    //列检测
    tempCnt0 = 1;
    for(i=1;board(dim[0],dim[1]+i)==1;i++)
      tempCnt0++;
    for(i=1;board(dim[0],dim[1]-i)==1;i++)
      tempCnt0++;
    if(tempCnt0 >= 5)
        return 256;
    tempCnt += tempCnt0;

    //正对角线检测
    tempCnt0 = 1;
    for(i=1,j=1;board(dim[0]+i,dim[1]+j)==1;i++,j++)
      tempCnt0++;
    for(i=1,j=1;board(dim[0]-i,dim[1]-j)==1;i++,j++)
      tempCnt0++;
    if(tempCnt0 >= 5)
        return 256;
    tempCnt += tempCnt0;

    //反对角线检测
    tempCnt0 = 1;
    for(i=1,j=1;board(dim[0]+i,dim[1]-j)==1;i++,j++)
      tempCnt0++;
    for(i=1,j=1;board(dim[0]-i,dim[1]+j)==1;i++,j++)
      tempCnt0++;
    if(tempCnt0 >= 5)
        return 256;
    tempCnt += tempCnt0;

    return tempCnt;
}
uint8 getValidPos(const BitBoard &table,const uint8 ran)
{
//    uint8 tempCnt=0;
//    for(uint8 t=0;t<16;t++)
//    {
//      for(uint8 k=0;k<16;k++)
//      {
//          uint8 pos = t*16 + k;
//          if(!(table[pos/8] & (1<<(pos%8))))//可落子，tempCnt加一
//          {
//              tempCnt++;
//              if(tempCnt >= ran)
//                  return pos;
//          }
//      }
//    }
    uint8 tempCnt=0;
    uint8 dim[2]={8,8};
    for(uint8 t=0;t<16;t++)
    {
      for(uint8 d=0;d<2;d++)
        for(uint8 k=0;k<=t;k++)
        {
          uint8 pos = dim[0]*16 + dim[1];
          if(!(table[pos/8] & (1<<(pos%8))))//可落子，tempCnt加一
              tempCnt++;
          if(t%2)
            dim[d]++;
          else
            dim[d]--;
          if(tempCnt >= ran)
              return pos;
        }
    }
    //找不到合适的值就返回0
    return 0;
}

uint8 MCGetValidPos(const BitBoard &inValidPos,const BitBoard &myBoard,const BitBoard &otherBoard)
{
    uint8 bestPos=0,bestValue=0;
    for(uint8 t=0;t<16;t++)
    {
      for(uint8 k=0;k<16;k++)
      {
          uint8 pos = t*16 + k;
          if(!(inValidPos[pos/8] & (1<<(pos%8))))//可落子，tempCnt加一
          {
                uint8 value1 = getPosValue(myBoard,pos);
                uint8 value2 = getPosValue(otherBoard,pos);
                uint8 value=0;
                if((2 + value1)<value2)
                    value=value2;
                else
                    value=value1;
                if(value>bestValue)
                {
                    bestValue = value;
                    bestPos = pos;
                }
          }
       }
    }
    return bestPos;
}

bool isWin(const BitBoard &board,const BitBoard &otherBoard,uint8 inp)
{
      uint8 dim[2] = {inp / 16, inp % 16};
      uint8 tempCnt = 1;
      bool isBlank = false;

      //行检测
      uint8 i=1,j=1;
      for(i=1;board(dim[0]+i,dim[1])==1;i++)
        tempCnt++;
      if(otherBoard(dim[0]+i,dim[1])==0)
          isBlank=true;
      for(i=1;board(dim[0]-i,dim[1])==1;i++)
        tempCnt++;
      if(otherBoard(dim[0]-i,dim[1])==0 && isBlank)
          if(tempCnt >= 4) return true;
      if(tempCnt >= 5 ) return true;

      //列检测
      tempCnt = 1;
      isBlank = false;
      for(i=1;board(dim[0],dim[1]+i)==1;i++)
        tempCnt++;
      if(otherBoard(dim[0],dim[1]+i)==0)
          isBlank = true;
      for(i=1;board(dim[0],dim[1]-i)==1;i++)
        tempCnt++;
      if(otherBoard(dim[0],dim[1]-i)==0 && isBlank)
          if(tempCnt >= 4) return true;
      if(tempCnt >= 5 ) return true;

      //正对角线检测
      tempCnt = 1;
      isBlank = false;
      for(i=1,j=1;board(dim[0]+i,dim[1]+j)==1;i++,j++)
        tempCnt++;
      if(otherBoard(dim[0]+i,dim[1]+j)==0)
          isBlank =true;
      for(i=1,j=1;board(dim[0]-i,dim[1]-j)==1;i++,j++)
        tempCnt++;
      if(otherBoard(dim[0]-i,dim[1]-j)==0 && isBlank)
          if(tempCnt >= 4) return true;
      if(tempCnt >= 5 ) return true;

      //反对角线检测
      tempCnt = 1;
      isBlank = false;
      for(i=1,j=1;board(dim[0]+i,dim[1]-j)==1;i++,j++)
        tempCnt++;
      if(otherBoard(dim[0]+i,dim[1]-j)==0)
          isBlank =true;
      for(i=1,j=1;board(dim[0]-i,dim[1]+j)==1;i++,j++)
        tempCnt++;
      if(otherBoard(dim[0]-i,dim[1]+j)==0 && isBlank)
          if(tempCnt >= 4) return true;
      if(tempCnt >= 5 ) return true;

      return false;
}

//由int数组生成AI中使用的位棋盘
ChessBoard::ChessBoard(int a[16][16],uint32 hash){
    for(unsigned char i=0;i<BOARDSIZE;i++)
        for(unsigned char j=0;j<BOARDSIZE;j++){
                uint8 block = ((i*16+j)/8);
                uint8  byteMask = (1<<((i*16+j)%8));
                if(a[i][j] == 2)
                    white[block] |= byteMask;
                if(a[i][j] == 1)
                    black[block] |= byteMask;
        }
    depth=0;
    value=-10001;
    parentValue=-10001;
    parentHash=hash;
}

//由父节点生成棋盘时所需要的构造
ChessBoard::ChessBoard(const ChessBoard &parent,uint8 inp,uint32 oldHash){
    //深度加1
    depth = parent.depth+1;
    //父节点的估计值00
    parentHash = oldHash;
    input = inp;
    white=parent.white;
    black=parent.black;
    value = -10001;
    parentValue = -parent.value;
    if(((realPly+depth)%2) != 0)//白子节点
    {
      if(isWin(black,white,inp))
          win = true;
      black[inp/8] |= (1<<(inp%8));
    }
    else
    {
      if(isWin(white,black,inp))
          win = true;
      white[inp/8] |= (1<<(inp%8));
    }
}

uint8 ChessBoard::operator ()(uint8 i,uint8 j){
    uint8 block = ((i*j)/8);
    uint8 byteMask = (1<<((i*j)%8));
    if(white[block] & byteMask)
        return 1;
    if(black[block] & byteMask)
        return 2;
    return 0;
}

int16 ChessBoard::run(){
    uint32 hash;
    if((realPly+depth) % 2)   //奇数,这是一个白子节点即min节点
       hash = ZobristHash(parentHash,input,1,0);   //这一步的是否可着子检测由父节点完成，信任父节点,inp为上一级的节点落的子，即黑子
    else
       hash = ZobristHash(parentHash,input,2,0);
    if(depth == maxDepth)//已到达最大深度
    {
        usleep(10);//线程挂起10微秒让根节点运行一下回收资源并分配新线程任务,解决方案略low ^_^!!!
        ZobristNode temp = {hash,0};
        bool isExist = false;
        std::vector<ZobristNode>::iterator k;
        ZobristNode h;
//        while(hashValuesLock[depth]);
//        hashValuesLock[depth] = true;
        pthread_mutex_lock(&hashMymutex[depth]);
        if((k=std::find(hashValues[depth]->begin(),hashValues[depth]->end(),temp))!=hashValues[depth]->end())
            isExist = true;
        if(isExist)
            h = *k;
        pthread_mutex_unlock(&hashMymutex[depth]);
//        hashValuesLock[depth] = false;
        if(!isExist){
          //尚未评估过该点，则使用蒙特卡洛方法评估
          h.value = MC();
          h.hash = hash;
          if(win)
              return h.value;
          //添加到置换表
          //以下两行对应P操作
//          while(hashValuesLock[depth]);//其他线程正在操作，阻塞
//          hashValuesLock[depth] = true;//对信号量执行-1操作哈
          pthread_mutex_lock(&hashMymutex[depth]);
          hashValues[depth]->push_back(h);
          //等效的V操作
          pthread_mutex_unlock(&hashMymutex[depth]);
//          hashValuesLock[depth] = false;

          if (h.value > parentValue)
            return (-10001);//返回一个无效收益,父节点会检测到它无效

          return (-h.value);//返回一个相反值
        }
        else{
          if(h.value > parentValue)
              return (-10001);
          return (-h.value);//返回一个相反值
        }
    }
    else if(depth!=0) //尚未到达最大深度
    {
        usleep(10);//线程挂起10微秒让根节点运行一下回收资源并分配新线程任务,解决方案略low ^_^!!!
        ZobristNode temp = {hash,0};
        bool isExist = false;
        std::vector<ZobristNode>::iterator k;
        ZobristNode h;
//        while(hashValuesLock[depth]);
//        hashValuesLock[depth] = true;
//        pthread_mutex_lock(&hashMymutex[depth]);
//        if((k=std::find(hashValues[depth]->begin(),hashValues[depth]->end(),temp))!=hashValues[depth]->end())
//            isExist = true;/////////////////////
        if(isExist)
            h = *k;
//        pthread_mutex_unlock(&hashMymutex[depth]);
//        hashValuesLock[depth] = false;
        if(!isExist){
        //尚未评估过该点
        BitBoard invalidPos;//用于确定那些点可以着子,为1的不可以
        uint8 validCap=256;//validCap有效点的个数

        //根据当前棋局得到那些点不能着子
        for(uint8 i=0;i<32;i++)
            invalidPos[i] |= (white[i] | black[i]);
        //更新可以着子的点的个数
        for(uint8 i=0;i<32;i++)
            for(uint8 j=0;j<8;j++)
              if((invalidPos[i] >> j) & 1)
                  validCap--;
        if(win)
        {
            value = validCap;
            return value;
        }
        //评估每个可以着子的点,直到所有点评估完成,根节点需要返回最佳输入值,且增加对多线程的支持
        while(validCap != 0)
        {
        // bool isValid = false;
        // while(!isValid)
        // {
          // 返回一个可以着子的位置,第一个参数是上面的棋子情况表
          uint8 inp = getValidPos(invalidPos);
          invalidPos[inp/8] |= (1<<(inp%8));
          // uint8 block = inp/8;
          // uint8 byteMask = 1 << (inp % 8 );
          // if(!(invalidPos[block] & byteMask))
          //     isValid = true;
        // }

          //新建节点开始评估
          ChessBoard *newNode = new ChessBoard(*this,inp,hash);
          int16 tempV = newNode->run();
          delete newNode;
          if(isValueValid(tempV))//若无效说明这个枝被cutoff，不处理
              if(value < tempV)//如果大于当前估计值则更新，其实没必要检测，只要有效就说明字节点已经检测通过
                  value = tempV;
          if(value > parentValue)//如果当前收益已经比父节点的负值还要大则无法更新父节点收益，cutoff
              return (-10001);
          validCap--;
        }
        //所有节点估计完毕
        //新的hash添加到置换表
        if(depth>1000)
        {
          h.value = value;
          h.hash = hash;
//          while(hashValuesLock[depth]);
//          hashValuesLock[depth] = true;
          pthread_mutex_lock(&hashMymutex[depth]);
          hashValues[depth]->push_back(h);
          pthread_mutex_unlock(&hashMymutex[depth]);
//          hashValuesLock[depth] = false;
          return(-h.value);
        }
        return (-value);
      }
      else
      {
            if(h.value > parentValue)
                return (-10001);
            return (-h.value);
      }
    }
      else if(depth == 0)
      {
        //初始化信号量和线程状态表
        for(uint8 p=0;p<maxThreads;p++)
        {
            hashValuesLock[p] = false;
            isTidJoin[p] = false;
        }
        hash = parentHash;
        int16 bestStep;
        //此段完成上面指针所指的内存实际分配，应该放在系统ai根节点开始阶段
        for(uint8 cnt=1;cnt<maxDepth-1;cnt++)
          hashValues[cnt] = hashValues[cnt+2];
        for(uint8 cnt=maxDepth-1;cnt<maxDepth+1;cnt++)
          hashValues[cnt] = new std::vector<ZobristNode>;
        //////////////////////////////////////////////////////////
          BitBoard invalidPos;//用于确定那些点可以着子,为1的不可以
          uint8 validCap=256;//validCap有效点的个数
          time(NULL);
          //根据当前棋局得到那些点不能着子
          for(uint8 i=0;i<32;i++)
              invalidPos[i] |= (white[i] | black[i]);
              //更新可以着子的点的个数
          for(uint8 i=0;i<32;i++)
            for(uint8 j=0;j<8;j++)
              if((invalidPos[i] >> j) & 1)
                  validCap--;
          uint8 validCapMin = validCap * 3/4;
          printf("validCap=%d\r\n",validCap);
        //评估每个可以着子的点,直到所有点评估完成,根节点需要返回最佳输入值,且增加对多线程的支持
          //建立新线程
          for(uint8 q=0;q<maxThreads;q++)
          {
//              sleep(1);//等待线程读取inp到本地栈
              uint8 inp = getValidPos(invalidPos);
              invalidPos[inp/8] |= (1<<(inp%8));
              ThreadArgs tempA = {this,inp,q};
              validCap--;
              isTidRunning[q] = true;
              pthread_create(&(tid[q]) , NULL , SearchThe , &tempA);
              usleep(10);
          }
          while(1)
          {
            if(validCap < validCapMin)
            {
              for(pthread_t q=0;q<maxThreads;q++)
              {
                if(!isTidJoin[q])
                {
                  //回收资源
                  void *tempP;
                  //阻塞
                  pthread_join(tid[q],&tempP);
                  int16 tempV = ((ThreadReturn *)tempP)->value;
                  int16 tempInp = ((ThreadReturn *)tempP)->inp;
                  delete tempP;
                  if(isValueValid(tempV))//若无效说明这个枝被cutoff，不处理
                      if(value < tempV)//如果大于当前估计值则更新，其实没必要检测，只要有效就说明字节点已经检测通过
                      {
                            value = tempV;
                            bestStep = tempInp;
                      }
                 }
              }
              break;
            }
            for(uint8 q=0;q<maxThreads;q++)
            {
              if(!isTidRunning[q])
              {
                //回收资源
                void *tempP;
                pthread_join(tid[q],&tempP);
                int16 tempV = ((ThreadReturn *)tempP)->value;
                int16 tempInp = ((ThreadReturn *)tempP)->inp;
                delete tempP;
                if(isValueValid(tempV))//若无效说明这个枝被cutoff，不处理
                    if(value < tempV)//如果大于当前估计值则更新，其实没必要检测，只要有效就说明字节点已经检测通过
                    {
                          value = tempV;
                          bestStep = tempInp;
                    }
                if(validCap >= validCapMin)
                {
                  uint8 inp = getValidPos(invalidPos);
                  invalidPos[inp/8] |= (1<<(inp%8));
                  ThreadArgs tempA = {this,inp,q};
                  validCap--;
                  isTidRunning[q] = true;
                  pthread_create(&(tid[q]) , NULL , SearchThe , &tempA);
                  usleep(10);//等待线程读取inp到本地栈
                }
                else
                {
                  //标记此tid对应的线程族已经回收完毕
                  isTidJoin[q] = true;
                }
              }
            }
            //usleep(10000);
          }
        //所有节点估计完
        /////////////////////////////////////////////////////////
        delete hashValues[1],hashValues[2];
        printf("bestStep=%d\r\n",bestStep);
        return bestStep;
    }
}
// static bool isAllThreadEnd()
// {
//   for(uint8 i=0;i<maxThreads;i++)
//     if(isTidRunning[i])
//       return false;
//   return true;
// }
int16 ChessBoard::MC(){
//MC函数可以获得到this对象的黑白棋盘情况，需要拷贝一份到栈空间，进行对弈模拟

    int16 whiteResult = 0,blackResult = 0;
    int16 result=0;
    bool isWhiteWin=false,isBlackWin=false;

    BitBoard *localWhite,*localBlack;
    for(int16 times=0;times<1;times++)
    {
//        printf("MC:%d start",times);
      //一局测试开始之前的准备工作
      //初始化棋盘
      localWhite = new BitBoard(white);
      localBlack = new BitBoard(black);

      BitBoard invalidPos;//用于确定那些点可以着子,为1的不可以
      uint8 validCap=256;   //有效点的个数

      //根据当前棋局得到哪些点不能着子
      for(uint8 i=0;i<32;i++)
          invalidPos[i] |= ((*localWhite)[i] | (*localBlack)[i]);
      //更新可以着子的点的个数
      for(uint8 i=0;i<32;i++)
          for(uint8 j=0;j<8;j++)
            if((invalidPos[i] >> j) & 1)
                validCap--;
      if(win)
      {
          value = validCap;
          return value;
      }

      bool isWhite = false;
        if((depth + realPly) % 2)//白子节点
          isWhite = true;

      //测试一局
      while(validCap) {
        if(isWhite)
        {
          uint8 inp = MCGetValidPos(invalidPos,*localWhite,*localBlack);
          if(isWin(*localWhite,*localBlack,inp))
          {
            result=validCap;
            isWhiteWin=true;
//            printf("white win inp = %d, validCap=%d\r\n",input,result);
            break;
          }
          (*localWhite)[inp/8] |= (1<<(inp%8));
          invalidPos[inp/8] |= (1<<(inp%8));
          validCap--;
        }
        else
        {
          uint8 inp = MCGetValidPos(invalidPos,*localBlack,*localWhite);
          if(isWin(*localBlack,*localWhite,inp))
          {
            result=validCap;
            isBlackWin=true;
//            printf("black win inp = %d, validCap=%d\r\n",input,result);
            break;
          }
          (*localBlack)[inp/8] |= (1<<(inp%8));
          invalidPos[inp/8] |= (1<<(inp%8));
          validCap--;
        }
      isWhite = !isWhite;
    }
    delete localWhite;
    delete localBlack;
//    printf("MC:%d finished",times);
  }
//    printf("inp:%d whiteResult=%d",input,whiteResult);
  if((depth + realPly) % 2)//白子节点
  {
    if(isWhiteWin)
        return result;
    else if(isBlackWin)
        return -result;
    else
        return 0;
  }
  else
  {
      if(isBlackWin)
          return result;
      else if(isWhiteWin)
          return -result;
      else
          return 0;
  }
}

//线程例程
static void *SearchThe(void *args)
{

//  printf("thread:%d\r\n",pthread_self());
  ThreadArgs mArgs = *((ThreadArgs *)args);

  //绑定核心
  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(mArgs.qtid % numProcessors , &mask);
  if(sched_setaffinity(0, sizeof(mask), &mask) == -1) //0 代表对当前线程
  {
      printf("set affinity failed..");
  }
//  printf("q = %d\r\n",mArgs.qtid);
  ////sleep(rand()%25);
  printf("q = %d start\r\n",mArgs.qtid);
  ChessBoard *newNode = new ChessBoard(*(mArgs.parent),mArgs.inp,hash);
  ThreadReturn *temp = new ThreadReturn;
  temp->value = newNode->run();
  temp->inp = mArgs.inp;
  delete newNode;
//  printf("q = %d finished\r\n",mArgs.qtid);
  isTidRunning[mArgs.qtid] = false;
  return temp;
}
