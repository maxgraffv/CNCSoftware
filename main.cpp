#include <iostream>
#include "cncSetup.h"
#include "stepperMotor.h"
#include "spindle.h"
#include "gCodeFile.h"
#include "unitsEnum.h"



int main()
{

    StepperMotor motorAxisZ;
    StepperMotor motorAxisY_1;
    StepperMotor motorAxisY_2;
    StepperMotor motorAxisX;
    Spindle spindle;



    CNCSetup myCNC( motorAxisX, motorAxisY_1, motorAxisY_2, motorAxisZ, spindle, Units::milimeter );
    GCodeFile operation1( "1001.ngc" );
    myCNC.run(operation1);


    // operation1.print();
    



    return 0;
}