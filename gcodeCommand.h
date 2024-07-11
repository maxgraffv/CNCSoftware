#ifndef GCODE_COMMAND_H
#define GCODE_COMMAND_H

#include <string>
#include "commandTypeFuncMap.h"

class GCodeCommand
{

    private:

        std::string commandStr;
        char commandType;
        int commandValue;
        int command;
        int priority;
        void (*commandFunc_ptr)();



    public:

        GCodeCommand( std::string commandStr );









};

#endif