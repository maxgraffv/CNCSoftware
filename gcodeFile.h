#ifndef GCODE_FILE_H
#define GCODE_FILE_H

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include "gcodeCommand.h"



class GCodeFile
{
    private:
        std::string gcodeStr;
        void semicolonCommentsRemove();
        void parenthesisCommentsRemove_byPair();
        void parenthesisCommentsRemove();
        void removePercentSign();
        void whiteSpacesRemove();
        void toCommandLines();
        void parse();
        void sortByPriority();
        std::vector<std::string> commandLines;
        std::vector< std::vector< GCodeCommand> > command_vec;
    public:
        GCodeFile( std::string gcode_path );
        void preprocess();
        void printGCodeStr();
        void printCommands();


        std::vector< std::vector< GCodeCommand> > getCommand_vec();




};





#endif