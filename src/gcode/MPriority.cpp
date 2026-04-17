#include "MPriority.h"

    int MPriority::getMPriority(double commandValue)
    {
        int priority = -1;
        if(commandValue >= 62 && commandValue <= 68)
            priority = 6;
        else if(commandValue == 6 || commandValue == 61)
            priority = 7; 
        else if(commandValue == 3 || commandValue == 4 || commandValue == 5)
            priority = 8;
        else if(commandValue == 70 || commandValue == 73 || 
                commandValue == 72 || commandValue == 71)
            priority = 9;
        else if(commandValue == 7 || commandValue == 8 || commandValue == 9)
            priority = 10; 
        else if( commandValue >= 48 && commandValue <= 53)
            priority = 11;
        else if( commandValue >= 100 && commandValue <= 199)
            priority = 12;
        else if(commandValue == 0 || commandValue == 1 || 
                commandValue == 2 || commandValue == 30 ||
                commandValue == 60
                )
            priority = 24;

        return priority;
       

    }


