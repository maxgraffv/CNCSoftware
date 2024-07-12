#ifndef CNC_SETUP_H
#define CNC_SETUP_H

#include <vector>
#include "stepperMotor.h"
#include "spindle.h"
#include "unitsEnum.h"
#include "gcodeFile.h"


class CNCSetup
{

    private:
        StepperMotor xAxisMotor;
        StepperMotor yAxisMotor1;
        StepperMotor yAxisMotor2;
        StepperMotor zAxisMotor;
        Spindle spindle;

        Units units;

        void processLine( std::vector< GCodeCommand > commandLine );

    public:
        CNCSetup(
            StepperMotor& xAxisMotor,
            StepperMotor& yAxisMotor1,
            StepperMotor& yAxisMotor2,
            StepperMotor& zAxisMotor,
            Spindle& spindle,
            Units units );

        static void moveX(double value);
        static void moveY(double value);
        static void moveZ(double value);
        void setXAxisMotor( StepperMotor& xAxisMotor );
        void setYAxisMotor( StepperMotor& xAxisMotor );
        void setZAxisMotor( StepperMotor& xAxisMotor );
        void setSpindle( Spindle& spindle );

        void run( GCodeFile gcodeFile );

};

#endif