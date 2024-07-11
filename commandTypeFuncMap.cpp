
#include <map>
#include <iostream>
#include <string>
#include "commandTypeFuncMap.h"
#include "cncSetup.h"




TypeFuncMap::TypeFuncMap()
{





    typeFuncMap['X'] = &CNCSetup::moveX;
    typeFuncMap['Y'] = &CNCSetup::moveY;
    typeFuncMap['Z'] = &CNCSetup::moveZ;



};


void (* TypeFuncMap::getFunc(char type))(double)
{
    return typeFuncMap[type];
}




