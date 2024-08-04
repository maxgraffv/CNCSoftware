#include <iostream>
#include "Tool.h"


Tool::Tool( double toolId ):id(toolId)
{
    std::cout << "created tool " << id << std::endl;
}

double Tool::getToolId()
{
    return id;
}

int Tool::setToolLengthOffset( double toolLengthOffset)
{
    this->toolLengthOffset = toolLengthOffset;   
    return 0;
}






