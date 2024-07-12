#include "GPriority.h"

    int GPriority::getGPriority(double commandValue)
    {
        int priority = -1;
        if(commandValue == 93 || commandValue == 94)
            priority = 2;
        else if(commandValue == 4)
            priority = 13;
        else if(commandValue == 17 || commandValue == 18 || commandValue == 19)
            priority = 14;
        else if(commandValue == 20 || commandValue == 21)
            priority = 15; 
        else if(commandValue == 40 || commandValue == 41 || commandValue == 42)
            priority = 16;
        else if(commandValue == 43 || commandValue == 49)
            priority = 17; 
        else if(commandValue >= 54 && commandValue <= 59.3)
            priority = 18;
        else if(commandValue == 61 || commandValue == 61.1 || commandValue == 64)
            priority = 19;
        else if(commandValue >= 90 && commandValue <= 91.1)
            priority = 20;
        else if(commandValue >= 98 && commandValue <= 99)
            priority = 21;
        else if(commandValue == 28 || commandValue == 30 || commandValue == 10 ||
            commandValue == 52 || commandValue == 92 || commandValue == 92.1 ||
            commandValue == 92.2 || commandValue == 94
        )
            priority = 22;
        else if( (commandValue >= 0 && commandValue <= 3) ||
            commandValue == 33 || commandValue == 73 || commandValue == 76 ||
            (commandValue >= 38.0 && commandValue < 39.0) ||
            (commandValue >= 80 && commandValue <= 89) || commandValue == 53
        )
            priority = 23;

        return priority;
       

    }


