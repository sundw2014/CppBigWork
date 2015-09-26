#include "mythread.h"
#include "AI.h"
#include <windows.h>

extern volatile bool isTidRunning[];

AIThread::AIThread(const ThreadArgs mArgs,QObject *parent):
    QThread(parent),
    Args(mArgs),
    stop(false)
{

}

void AIThread::run()
{
      //绑定核心
//      unsigned char mask = 1<<(Args.qtid % numProcessors);
//      SetThreadAffinityMask(((::HANDLE)currentThreadId()), mask);

      printf("q = %d start,inp = %d\r\n",Args.qtid,Args.inp);
      ChessBoard *newNode = new ChessBoard(*(Args.parent),Args.inp,Args.hash);
      result.value = newNode->run();
      result.inp = Args.inp;
      delete newNode;
    //  printf("q = %d finished\r\n",mArgs.qtid);
      stop = true;
}
