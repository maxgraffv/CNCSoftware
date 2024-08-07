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
#include <sstream>
#include <cstdlib>
#include <csignal>
#include <unistd.h>


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


void program( std::vector<std::string> args, CNCSetup& myCNC);

void handleSIGTSTP(int signal);

CNCSetup* cncSetupPTR = nullptr;

int main( int argc, char** argv )
{ 

    signal(SIGTSTP, handleSIGTSTP);
    signal(SIGINT, handleSIGTSTP);

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
    cncSetupPTR = &myCNC; //for program exit handling SIGTSTP


    std::vector< std::string > args;
    std::string line, word;
    std::istringstream stream;

    switch( argc )
    {
        case 1:
            while(true)
            {
                std::cout << "GraffOS ";

                std::getline(std::cin, line); 
                stream = std::istringstream(line);
                while( stream >> word )
                    args.push_back(word);
                if(!args.empty())
                    program( args, myCNC );
                args.clear();
            }
            break;
        default:
            for(int i = 1; i < argc; i++)
                args.push_back(argv[i]);
            program( args, myCNC );
    }

    return 0;
}

void handleSIGTSTP( int signal )
{
    std::cout << "Program Stopped Unexpectedly" << std::endl;
    std::cout << "System shutdown..." << std::endl;
    cncSetupPTR->systemDisable();
    std::cout << "Shutdown COMPLETE" << std::endl;
    std::exit(0);
}

void program( std::vector<std::string> args, CNCSetup& myCNC)
{

    if( args[0] == "run" )
    {
        GCodeFile operation1( args[1] );
        myCNC.run(operation1);
    }
    if( args[0] == "info" )
    {
        std::cout << "current position X: " << myCNC.getAbsolutePos()[0] << std::endl;
        std::cout << "current position Y: " << myCNC.getAbsolutePos()[1] << std::endl;
        std::cout << "current position Z: " << myCNC.getAbsolutePos()[2] << std::endl;
    }
    if( args[0] == "moveby" )
    {
        double f = 1000;
        double x = 0;
        double y = 0;
        double z = 0;

        std::string word;
        for(int i = 1; i < args.size(); i++)
        {
            if(args[i][0] == '-' && args[i][1] == 'x')
            {
                word = std::string( args[i].begin()+2, args[i].end() );
                x = std::stod(word);
            }
            else if(args[i][0] == '-' && args[i][1] == 'y')
            {
                word = std::string( args[i].begin()+2, args[i].end() );
                y = std::stod(word);
            }
            else if(args[i][0] == '-' && args[i][1] == 'z')
            {
                word = std::string( args[i].begin()+2, args[i].end() );
                z = std::stod(word);
            }
            else if(args[i][0] == '-' && args[i][1] == 'f')
            {
                word = std::string( args[i].begin()+2, args[i].end() );
                f = std::stod(word);
            }
            else
            {
                std::cout << "Error: unknown flag" << std::endl;
                break;
            }
        }

        std::cout << "moving by: " << x << " " << y << " " << z << std::endl;
        myCNC.feedrateMoveBy(f,x,y,z );

    }
    if( args[0] == "moveto" )
    {
        
    }
    if( args[0] == "home" )
    {
        myCNC.home();
    }
    if( args[0] == "help" )
    {

    }
    if( args[0] == "set" )
    {

    }
    if( args[0] == "mdi" )//manual data input
    {

    }
    if( args[0] == "quit" )
    {
        cncSetupPTR->systemDisable();
        std::exit(0);
    }

    



}