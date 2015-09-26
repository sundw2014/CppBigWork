#include "statemachine.h"
#include "client.hpp"
#include <QtWidgets>

StateMachine::StateMachine(Own1 &mgame,Client &mclient,QObject *parent):
    QThread(parent),
    game(mgame),
    client(mclient)
{}
StateMachine::~StateMachine()
{}
STATE StateMachine::runOnce()
{
    switch (state)
    {
        case WAIT:
        {
            while(1)
            {
                if(client.updateFrame())
                    if(client.frame.cmd == std::string("START"))
                    {
                        state = YOURTURN;
                        break;
                    }
            }
            break;
        }
        case YOURTURN:
        {
            break;
        }
        case OTHSTURN:
        {
            while(1)
            {
                if(client.updateFrame())
                     if(client.frame.cmd == std::string("NEWINP"))
                     {
                         uint8 inp =  *(unsigned char *)(client.receivedFrame->value1);
                         if(game.inp(inp,3-game.myTurn()))
                         {}
                         else
                         {}
                         if(game.Win(inp/16,inp%16))
                         {
                             unsigned char tempLen[4] = {5,0,0,0};

                             client.sendFrame(tempLen,"ILOSE");
                             //QMessageBox::information((QDialog *)parent(), "lose", "YOU LOSE", QMessageBox::Ok);
                             state = LOSE;
                             break;
                         }
                         state = YOURTURN;
                         break;
                     }
            }
            break;
        }
        case OVER:
            break;
        case LOSE:
            break;
        defalut:
            break;
    }
    return state;
}
