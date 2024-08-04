#ifndef TOOL_H
#define TOOL_H

class Tool
{

    private:
        double id;
        double toolLengthOffset;


    public:
        Tool( double toolId );
        double getToolId();
        int setToolLengthOffset( double toolLengthOffset);




};

#endif

