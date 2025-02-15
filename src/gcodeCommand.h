#ifndef GCODE_COMMAND_H
#define GCODE_COMMAND_H

#include <string>

class GCodeCommand
{

    private:

        std::string commandStr;
        char commandType;
        double commandValue;
        int priority;
        void (*commandFunc_ptr)();
        void setPriority();



    public:

        GCodeCommand( std::string commandStr );
        char getCommandType();
        double getCommandValue();
        int getPriority();









};

#endif