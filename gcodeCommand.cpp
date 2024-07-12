#include <string>

#include "gcodeCommand.h"



GCodeCommand::GCodeCommand( std::string commandStr )
{
    commandType = commandStr[0];
    commandStr.erase(0, 1);
    commandValue = std::stod( commandStr );
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