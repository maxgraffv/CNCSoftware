#include <vector>
#include "stepperMotor.h"
#include "cncSetup.h"
#include "gcodeFile.h"




    CNCSetup::CNCSetup( 
            StepperMotor& xAxisMotor, StepperMotor& yAxisMotor1,
            StepperMotor& yAxisMotor2, StepperMotor& zAxisMotor,
            Spindle& spindle, Units units = Units::milimeter) 
            : xAxisMotor(xAxisMotor), yAxisMotor1(yAxisMotor1),
                yAxisMotor2(yAxisMotor2), zAxisMotor(zAxisMotor),
                spindle(spindle), units(units)
    {

    }

    void CNCSetup::moveX(double value)
    {

    }

    void CNCSetup::moveY(double value)
    {

    }

    void CNCSetup::moveZ(double value)
    {

    }






    void CNCSetup::run( GCodeFile gcodeFile )
    {


        // std::vector< std::vector< GCodeCommand> > command_vec = gcodeFile.getCommand_vec();

        gcodeFile.printCommands();












    }