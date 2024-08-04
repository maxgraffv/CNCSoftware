#include <iostream>
#include "cncSetup.h"
#include "stepperMotor.h"
#include "spindle.h"
#include "gcodeFile.h"
#include "unitsEnum.h"
#include "microstepResolutionEnum.h"
#include "MotorRotationDirectionEnum.h"
#include "LimitSwitch.h"
#include "rpi3pinout.h"
#include <thread>
#include <functional>
#include <stdexcept>

/*
FOR GPIO14 GPIO15 to work, UART has to be disabled

sudo nano /boot/cmdline.txt
Remove console=serial0,115200 or console=ttyAMA0,115200

sudo nano /boot/config.txt
enable_uart=0
dtoverlay=pi3-disable-bt

# Wyłącz I2C ID EEPROM
#dtparam=i2c_vc=on
# Możesz również upewnić się, że I2C1 jest wyłączony
#dtparam=i2c_arm=on




sudo reboot
*/



int main( int argc, char** argv )
{
    std::vector< std::string > args;

    for(int i = 0; i < argc; i++)
        args.push_back(argv[i]);

    
    

    StepperMotor motorAxisZ( GPIO17 , GPIO27 , GPIO22, GPIO14, GPIO15, MicrostepResolution::EIGHTH_STEP, MotorRotationDirection::CLOCKWISE, 2);
    StepperMotor motorAxisY_1(GPIO23 , GPIO24, GPIO10, GPIO9, GPIO11, MicrostepResolution::EIGHTH_STEP, MotorRotationDirection::CLOCKWISE, 8);
    StepperMotor motorAxisY_2( GPIO25, GPIO8, GPIO7, GPIO5, GPIO6, MicrostepResolution::EIGHTH_STEP, MotorRotationDirection::CLOCKWISE, 8);
    StepperMotor motorAxisX( GPIO13, GPIO19, GPIO16, GPIO26, GPIO20, MicrostepResolution::EIGHTH_STEP, MotorRotationDirection::CLOCKWISE, 8);
    Spindle spindle(GPIO18, GPIO4);

    LimitSwitch limitSwitchX(GPIO21);
    LimitSwitch limitSwitchY(GPIO12);
    LimitSwitch limitSwitchZ(GPIO0);
    LimitSwitch limitSwitchT(GPIO1);



    CNCSetup myCNC( motorAxisX, motorAxisY_1, motorAxisY_2, motorAxisZ, spindle,
        limitSwitchX, limitSwitchY, limitSwitchZ, limitSwitchT, Units::milimeter );

    std::string user_input;
    switch( argc )
    {
        case 1:
            // enterProgram();
            std::cout << "GraffOS "; std::cin >> user_input;
            break;
        case 3:
            if( args[1] == "run" )
            {
                GCodeFile operation1( args[2] );
                myCNC.run(operation1);
            }
            break;
        default:
            throw std::runtime_error("Error: unknown argument");

    }



    



    return 0;
}