#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_
#include "mType.h"
#include "client.hpp"
#include "own1.h"
#include "qthread.h"

class Own1;

enum STATE {WAIT=0,YOURTURN,OTHSTURN,OVER};

class StateMachine:public QThread
{
    Q_OBJECT
private:
    Client &client;
    STATE state;
    Own1 &game;
public:
    StateMachine(Own1 &mgame,Client &mclient,QObject *parent = 0);
    STATE runOnce();
    STATE setState(const STATE &newState)
    {
        state = newState;
        return state;
    }
    STATE getSTATE(){return state;}
    void run()
    {
        runOnce();
    }
};

#endif // STATEMACHINE

