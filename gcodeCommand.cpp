#include <string>
#include <iostream>
#include "gcodeCommand.h"
#include "GPriority.h"
#include "MPriority.h"



GCodeCommand::GCodeCommand( std::string commandStr )
{
    commandType = commandStr[0];
    commandStr.erase(0, 1);
    commandValue = std::stod( commandStr );
    setPriority();

}

char GCodeCommand::getCommandType()
{
    return commandType;
}

double GCodeCommand::getCommandValue()
{
    return commandValue;
}



int GCodeCommand::getPriority()
{
    return priority;
}

void GCodeCommand::setPriority()
{
    int p = -1;
    switch(commandType)
    {
        case 'A':
            std::cout << "Priority unknown: " << commandType << std::endl;
            break;

        case 'B':
            std::cout << "Priority unknown: " << commandType << std::endl;
            break;

        case 'C':
            std::cout << "Priority unknown: " << commandType << std::endl;
            break;

        case 'D':
            std::cout << "Priority unknown: " << commandType << std::endl;
            break;

        case 'E':
            std::cout << "Priority unknown: " << commandType << std::endl;
            break;

        case 'F':
            priority = 3;
            break;

        case 'G':
            priority = GPriority::getGPriority(commandValue);
            break;

        case 'H':
            priority = 17;
            break;

        case 'I':
            priority = 23;
            break;

        case 'J':
            priority = 23;
            break;

        case 'K':
            std::cout << "Priority unknown: " << commandType << std::endl;
            break;

        case 'L':
            std::cout << "Priority unknown: " << commandType << std::endl;
            break;

        case 'M':
            priority = MPriority::getMPriority(commandValue);
            break;

        case 'N':
            priority = -1;
            break;

        case 'O':
            priority = 0;
            break;

        case 'P':
            priority = 19;
            break;

        case 'Q':
            priority = 19;
            break;

        case 'R':
            std::cout << "Priority unknown: " << commandType << std::endl;
            break;

        case 'S':
            priority = 4;
            break;

        case 'T':
            priority = 5;
            break;

        case 'U':
            std::cout << "Priority unknown: " << commandType << std::endl;
            break;

        case 'V':
            std::cout << "Priority unknown: " << commandType << std::endl;
            break;

        case 'W':
            std::cout << "Priority unknown: " << commandType << std::endl;
            break;

        case 'X':
            priority = 23;
            break;

        case 'Y':
            priority = 23;
            break;

        case 'Z':
            priority = 23;
            break;
        default:
            std::cout << "Priority unknown: " << commandType << std::endl;

    };

}