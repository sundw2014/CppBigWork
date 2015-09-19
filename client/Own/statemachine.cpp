#include "statemachine.h"
#include "client.hpp"
#include <QtWidgets>

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
                         if(game.inp(inp,game.myTurn()))
                         {}
                         else
                         {}
                         if(game.Win(inp/16,inp%16))
                         {
                             unsigned char tempLen[4] = {5,0,0,0};

                             client.sendFrame(tempLen,"ILOSE");
                             QMessageBox::information(0, "lose", "YOU LOSE", QMessageBox::Ok);
                             state = OVER;
                             break;
                         }
                         state = YOURTURN;
                         break;
                     }
            }
            break;
        }
    }
}
