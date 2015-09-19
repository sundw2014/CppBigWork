#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_
#include "mType.h"
#include "client.hpp"
#include "own1.h"

class Own1;

enum STATE {WAIT=0,YOURTURN,OTHSTURN,OVER};

class StateMachine
{
private:
    Client &client;
    STATE state;
    Own1 &game;
public:
    StateMachine(Own1 &mgame,Client &mclient):game(mgame),client(mclient){}
    STATE runOnce();
    STATE setState(const STATE &newState)
    {
        state = newState;
        return state;
    }
    STATE getSTATE(){return state;}
};

#endif // STATEMACHINE

