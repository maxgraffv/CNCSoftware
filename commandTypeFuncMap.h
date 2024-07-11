#ifndef COMMAND_TYPE_FUNC_MAP_H
#define COMMAND_TYPE_FUNC_MAP_H

#include <map>
#include <iostream>
#include <string>
#include "cncSetup.h"




class TypeFuncMap
{
    private:
        std::map< char, void(*)(double) > typeFuncMap;

    public:
        TypeFuncMap();
        void ( *getFunc(char Type))(double);


};






#endif