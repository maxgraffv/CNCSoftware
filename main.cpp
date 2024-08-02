#include <iostream>
#include "cncSetup.h"
#include "stepperMotor.h"
#include "spindle.h"
#include "gcodeFile.h"
#include "unitsEnum.h"
#include "microstepResolutionEnum.h"
#include "MotorRotationDirectionEnum.h"
#include "rpi3pinout.h"
#include <thread>
#include <functional>

/*
FOR GPIO14 GPIO15 to work, UART has to be disabled

sudo nano /boot/cmdline.txt
Remove console=serial0,115200 or console=ttyAMA0,115200

sudo nano /boot/config.txt
enable_uart=0
dtoverlay=pi3-disable-bt

sudo reboot
*/

int main()
{

    StepperMotor motorAxisZ( GPIO17 , GPIO27 , GPIO22, GPIO14, GPIO15, MicrostepResolution::EIGHTH_STEP, MotorRotationDirection::CLOCKWISE, 2);
    StepperMotor motorAxisY_1(GPIO23 , GPIO24, GPIO10, GPIO9, GPIO11, MicrostepResolution::EIGHTH_STEP, MotorRotationDirection::CLOCKWISE, 8);
    StepperMotor motorAxisY_2( GPIO25, GPIO8, GPIO7, GPIO5, GPIO6, MicrostepResolution::EIGHTH_STEP, MotorRotationDirection::CLOCKWISE, 8);
    StepperMotor motorAxisX( GPIO13, GPIO19, GPIO16, GPIO26, GPIO20, MicrostepResolution::EIGHTH_STEP, MotorRotationDirection::CLOCKWISE, 8);
    Spindle spindle(GPIO2, GPIO3);




    CNCSetup myCNC( motorAxisX, motorAxisY_1, motorAxisY_2, motorAxisZ, spindle, Units::milimeter );
    GCodeFile operation1( "103.ngc" );
    myCNC.run(operation1);


    



    return 0;
}