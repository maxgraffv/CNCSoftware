#include <vector>
#include "stepperMotor.h"
#include "cncSetup.h"
#include "gcodeFile.h"
#include "motionTypeEnum.h"
#include "motionPlaneEnum.h"
#include "unitsEnum.h"
#include <math.h>
#include "distanceMode.h"
#include "arcDistanceMode.h"
#include "spindleState.h"
#include "Tool.h"
#include <thread>
#include <functional>




CNCSetup::CNCSetup( 
        StepperMotor& xAxisMotor, StepperMotor& yAxisMotor1,
        StepperMotor& yAxisMotor2, StepperMotor& zAxisMotor,
        Spindle& spindle, Units units = Units::milimeter) 
        : xAxisMotor(xAxisMotor), yAxisMotor1(yAxisMotor1),
            yAxisMotor2(yAxisMotor2), zAxisMotor(zAxisMotor),
            spindle(spindle), units(units), posX(0), posY(0), posZ(0), currentTool(0)
{

}


void CNCSetup::run( GCodeFile &gcodeFile )
{


    std::vector< std::vector< GCodeCommand> > command_vec 
        = gcodeFile.getCommand_vec();


    for( int i = 0; i < command_vec.size(); i++ )
    {
        process( command_vec[i] );




    }

    // for( int i = 0; i < command_vec.size(); i++)
    // {
    //     for(int j = 0; j < command_vec[i].size(); j++)
    //         std::cout << command_vec[i][j].getPriority() << "[" << command_vec[i][j].getCommandType() << "]("<<command_vec[i][j].getCommandValue() << ") ";
    //     std::cout << std::endl;
    // }
    // gcodeFile.printCommands();

}

void CNCSetup::process( std::vector< GCodeCommand >& command_line )
{
    int letter_count = command_line.size();
    int letters_used = 0;


    while( !command_line.empty() )
    {
        if( !containsCodeType(command_line, 'G') && command_line[0].getPriority() == 23 )
            CNCSetup::setMotionType(getMotionType(), command_line); //makes a motion of a type set beforehand
        else
            execute( command_line );
    }

}


int CNCSetup::execute( std::vector< GCodeCommand >& command_line )
{
    int letters_used = 0;
    GCodeCommand command = command_line[0];

    command_line.erase(command_line.begin(), command_line.begin() + 1 );
    letters_used++;

    switch(command.getCommandType())
    {
        case 'N':
            std::cout << "Code Line: " << command.getCommandValue() << std::endl;
            break;
        case 'G':
            if( command.getCommandValue() == 0 )
                letters_used += CNCSetup::setMotionType( MotionTypeEnum::RapidPositioning, command_line );
            else if( command.getCommandValue() == 1 )
                letters_used += CNCSetup::setMotionType( MotionTypeEnum::LinearInterpolation, command_line );
            else if( command.getCommandValue() == 2 )
                letters_used += CNCSetup::setMotionType( MotionTypeEnum::CircularInterpolationClockwise, command_line );
            else if( command.getCommandValue() == 3 )
                letters_used += CNCSetup::setMotionType( MotionTypeEnum::CircularInterpolationCounterClockwise, command_line );
            // else if( command.getCommandValue() == 4 )
            //     CNCSetup::dwell();
            // else if( command.getCommandValue() == 10 )
            //     CNCSetup::coordinateSystemOriginSetting();
            else if( command.getCommandValue() == 17 )
                letters_used = CNCSetup::setMotionPlane( MotionPlane::XY );
            else if( command.getCommandValue() == 18 )
                letters_used = CNCSetup::setMotionPlane( MotionPlane::XZ );
            else if( command.getCommandValue() == 19 )
                letters_used = CNCSetup::setMotionPlane( MotionPlane::YZ );
            else if( command.getCommandValue() == 20 )
                letters_used = CNCSetup::setUnits( Units::inch );
            else if( command.getCommandValue() == 21 )
                letters_used = CNCSetup::setUnits( Units::milimeter );
            // else if( command.getCommandValue() == 28 )
            //     CNCSetup::returnHome();
            // else if( command.getCommandValue() == 30 )
            //     CNCSetup::returnSecondaryHome();
            // else if( command.getCommandValue() == 38.2 )
            //     CNCSetup::straightProbe();
            // else if( command.getCommandValue() == 40 )
            //     CNCSetup::cancelCutterRadiusCompensation();
            // else if( command.getCommandValue() == 41 )
            //     CNCSetup::toolRadiusCompensationLeft();
            // else if( command.getCommandValue() == 42 )
            //     CNCSetup::toolRadiusCompensationRight();
            // else if( command.getCommandValue() == 43 )
            // else if( command.getCommandValue() == 18 )
            //     CNCSetup::selectXZPlane();
            // else if( command.getCommandValue() == 19 )
            //     CNCSetup::selectYZPlane();
            // else if( command.getCommandValue() == 20 )
            //     CNCSetup::setUnits( Units::inch );
            // else if( command.getCommandValue() == 21 )
            //     CNCSetup::setUnits( Units::milimeter );
            // else if( command.getCommandValue() == 28 )
            //     CNCSetup::returnHome();
            // else if( command.getCommandValue() == 30 )
            //     CNCSetup::returnSecondaryHome();
            // else if( command.getCommandValue() == 38.2 )
            //     CNCSetup::straightProbe();
            // else if( command.getCommandValue() == 40 )
            //     CNCSetup::cancelCutterRadiusCompensation();
            // else if( command.getCommandValue() == 41 )
            //     CNCSetup::toolRadiusCompensationLeft();
            // else if( command.getCommandValue() == 42 )
            //     CNCSetup::toolRadiusCompensationRight();
            // else if( command.getCommandValue() == 43 )
            // else if( command.getCommandValue() == 18 )
            //     CNCSetup::selectXZPlane();
            // else if( command.getCommandValue() == 19 )
            //     CNCSetup::selectYZPlane();
            // else if( command.getCommandValue() == 20 )
            //     CNCSetup::setUnits( Units::inch );
            // else if( command.getCommandValue() == 21 )
            //     CNCSetup::setUnits( Units::milimeter );
            // else if( command.getCommandValue() == 28 )
            //     CNCSetup::returnHome();
            // else if( command.getCommandValue() == 30 )
            //     CNCSetup::returnSecondaryHome();
            // else if( command.getCommandValue() == 38.2 )
            //     CNCSetup::straightProbe();
            // else if( command.getCommandValue() == 40 )
            //     CNCSetup::cancelCutterRadiusCompensation();
            // else if( command.getCommandValue() == 41 )
            //     CNCSetup::toolRadiusCompensationLeft();
            // else if( command.getCommandValue() == 42 )
            //     CNCSetup::toolRadiusCompensationRight();
            else if( command.getCommandValue() == 43 )
                letters_used = CNCSetup::setToolLengthOffset( command_line );
            else if( command.getCommandValue() == 49 )
                CNCSetup::cancelToolLengthOffset();
            // else if( command.getCommandValue() == 53 )
            //     CNCSetup::moveInMachineCoordinateSystem();
            // else if( command.getCommandValue() == 54 )
            //     CNCSetup::usePresetWorkCoordinateSys1();
            // else if( command.getCommandValue() == 55 )
            //     CNCSetup::usePresetWorkCoordinateSys2();
            // else if( command.getCommandValue() == 56 )
            //     CNCSetup::usePresetWorkCoordinateSys3();
            // else if( command.getCommandValue() == 57 )
            //     CNCSetup::usePresetWorkCoordinateSys4();
            // else if( command.getCommandValue() == 58 )
            //     CNCSetup::usePresetWorkCoordinateSys5();
            // else if( command.getCommandValue() == 59 )
            //     CNCSetup::usePresetWorkCoordinateSys6();
            else if( command.getCommandValue() == 61 )
                CNCSetup::setPathMode( PathMode::Exact, command_line );
            else if( command.getCommandValue() == 61.1 )
                CNCSetup::setPathMode( PathMode::ExactStop, command_line );
            else if( command.getCommandValue() == 64 )
                CNCSetup::setPathMode( PathMode::Blending, command_line );
            // else if( command.getCommandValue() == 76 )
            //     CNCSetup::threadCuttingCycle();
            // else if( command.getCommandValue() == 80 )
            //     CNCSetup::cancelMotionMode();
            // else if( command.getCommandValue() == 81 )
            //     CNCSetup::simpleDrillingCycle();
            // else if( command.getCommandValue() == 82 )
            //     CNCSetup::drillingCycleWithDwell();
            // else if( command.getCommandValue() == 83 )
            //     CNCSetup::peckDrillingCycle();
            // else if( command.getCommandValue() == 84 )
            //     CNCSetup::tappingCycle();
            // else if( command.getCommandValue() == 85 )
            //     CNCSetup::boringCycle();
            // else if( command.getCommandValue() == 86 )
            //     CNCSetup::boringCycleSpindleStop();
            // else if( command.getCommandValue() == 87 )
            //     CNCSetup::backBoringCycle();
            // else if( command.getCommandValue() == 88 )
            //     CNCSetup::boringCycleManualRetraction();
            // else if( command.getCommandValue() == 89 )
            //     CNCSetup::boringCycleWithDwell();
            else if( command.getCommandValue() == 90 )
                CNCSetup::setDistanceMode(DistanceMode::absoluteDistance);
            else if( command.getCommandValue() == 90.1 )
                CNCSetup::setArcDistanceMode( ArcDistanceMode::absolute );
            else if( command.getCommandValue() == 91 )
                CNCSetup::setDistanceMode(DistanceMode::incrementalDistance);
            else if( command.getCommandValue() == 91.1 )
                CNCSetup::setArcDistanceMode( ArcDistanceMode::incremental );
            // else if( command.getCommandValue() == 92 )
            //     CNCSetup::setCurrentPositionToCoordinatesGiven();
            // else if( command.getCommandValue() == 93 )
            //     CNCSetup::inverseTimeFeedRateMode();
            else if( command.getCommandValue() == 94 )
                letters_used = CNCSetup::setFeedMode( FeedMode::feedPerMinute );
            else if( command.getCommandValue() == 95 )
                letters_used = CNCSetup::setFeedMode( FeedMode::feedPerRevolution );
            // else if( command.getCommandValue() == 96 )
            //     CNCSetup::constantSurfaceSpeed();
            // else if( command.getCommandValue() == 97 )
            //     CNCSetup::cancelConstantSurfaceSpeed();
            // else if( command.getCommandValue() == 98 )
            //     CNCSetup::returnToInitialLevelCannedCycles();
            // else if( command.getCommandValue() == 99 )
            //     CNCSetup::returnToRPointInCannedCycles();
            else
                std::cout << " UNKNOWN G-Code Value - unable to execute() " << command.getCommandValue() << std::endl;

            break;

        case 'M':
            if( command.getCommandValue() == 0 )
                CNCSetup::programPause();
            // else if( command.getCommandValue() == 1 )
            //     CNCSetup::optionalStop();
            // else if( command.getCommandValue() == 2 )
            //     CNCSetup::programEnd();
            else if( command.getCommandValue() == 3 )
                CNCSetup::setSpindleState(SpindleState::ONClockwise, command_line );
            else if( command.getCommandValue() == 4 )
                CNCSetup::setSpindleState(SpindleState::ONCounterClockwise, command_line );
            else if( command.getCommandValue() == 5 )
                CNCSetup::setSpindleState(SpindleState::OFF, command_line );
            else if( command.getCommandValue() == 6 )
                CNCSetup::toolChange();
            // else if( command.getCommandValue() == 7 )
            //     CNCSetup::mistCoolantOn();
            // else if( command.getCommandValue() == 8 )
            //     CNCSetup::floodCoolantOn();
            // else if( command.getCommandValue() == 9 )
            //     CNCSetup::coolantOff();
            else if( command.getCommandValue() == 30 )
                CNCSetup::programStop();
            // else if( command.getCommandValue() == 48 )
            //     CNCSetup::enableSpeedFeedOverride();
            // else if( command.getCommandValue() == 49 )
            //     CNCSetup::disableSpeedFeedOverride();
            // else if( command.getCommandValue() == 60 )
            //     CNCSetup::palletChange();
            // else if( command.getCommandValue() == 98 )
            //     CNCSetup::subprogramCall();
            // else if( command.getCommandValue() == 99 )
            //     CNCSetup::returnFromSubprogramOrEndProgram();
            else
            std::cout << " UNKNOWN M-Code Value - unable to execute() " << command.getCommandValue() << std::endl;
            break;

        case 'F':
            letters_used += CNCSetup::setFeedRate( command.getCommandValue() );
            break;
        case 'S':
            std::cout << " Speed Set: " << command.getCommandValue() << std::endl;
            break;
        case 'T':
            CNCSetup::setNewTool( command.getCommandValue() );
            break;
        case 'H':

            break;
        default:
            std::cout << "TF is happening b- cncSetup execute()" << command.getCommandType() << command.getCommandValue() << std::endl;
    }

    return letters_used;
}

int CNCSetup::setFeedRate( double feedRate )
{
    this->feedRate = feedRate;
    std::cout << "Feedrate set to: " << feedRate << std::endl;
    return 0;

}

double CNCSetup::getFeedRate()
{
    return feedRate;
}




bool containsCodeType(std::vector< GCodeCommand > command_vec, char c)
{
    bool contains = false;
    for(int i = 0; i < command_vec.size(); i++)
        if( command_vec[i].getCommandType() == c )
            contains = true;

    return contains;
}




int CNCSetup::setMotionType( MotionTypeEnum motionType, std::vector<GCodeCommand>& command_line )
{
    int letters_used = 0;
    double X = 0;
    double Y = 0;
    double Z = 0;
    double I = 0;
    double J = 0;
    double K = 0;

    int commandLineSize = command_line.size();
    for( int i = 0; i < commandLineSize; i++)
    {
        if(command_line[i].getCommandType() == 'X')
        {
            X = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            letters_used++;
            i--;
            commandLineSize--;
            std::cout << "X";
        }else

        if(command_line[i].getCommandType() == 'Y')
        {
            Y = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            letters_used++;
            i--;
            commandLineSize--;
            std::cout << "Y";
        }else

        if(command_line[i].getCommandType() == 'Z')
        {
            Z = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            letters_used++;
            i--;
            commandLineSize--;
            std::cout << "Z";

        }else
        
        if(command_line[i].getCommandType() == 'I')
        {
            I = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            letters_used++;
            i--;
            commandLineSize--;
            std::cout << "I";

        }else

        if(command_line[i].getCommandType() == 'J')
        {
            J = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            letters_used++;
            i--;
            commandLineSize--;
            std::cout << "X";

        }else

        if(command_line[i].getCommandType() == 'K')
        {
            K = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            letters_used++;
            i--;
            commandLineSize--;
            std::cout << "X";
        }
        else
            std::cout << "UNKNOWN MOTION PARAMETER "<<std::endl;
    }

    move(X,Y,Z,I,J,K);

    return letters_used;

}


void CNCSetup::move(double newX, double newY, double newZ, double i, double j, double k)
{
    switch( motionType )
    {
        case MotionTypeEnum::RapidPositioning :
            switch( distanceMode )
            {
                case DistanceMode::absoluteDistance :
                    double currentX = absolutePosX;
                    double currentY = absolutePosY;
                    double currentZ = absolutePosZ;

                    double deltaX = newX - currentX;
                    double deltaY = newY - currentY;
                    double deltaZ = newZ - currentZ;

                    rapidMoveBy(deltaX, deltaY, deltaZ);
                    break;
                case DistanceMode::incrementalDistance :
                    rapidMoveBy(newX, newY, newZ);
                    break;
            }
            break;
        case MotionTypeEnum::LinearInterpolation :
            switch( distanceMode )
            {
                case DistanceMode::absoluteDistance :
                    double currentX = absolutePosX;
                    double currentY = absolutePosY;
                    double currentZ = absolutePosZ;

                    double deltaX = newX - currentX;
                    double deltaY = newY - currentY;
                    double deltaZ = newZ - currentZ;

                    feedrateMoveBy(deltaX, deltaY, deltaZ);
                    break;
                case DistanceMode::incrementalDistance :
                    feedrateMoveBy(newX, newY, newZ);
                    break;
            }
            break;
        case MotionTypeEnum::CircularInterpolationClockwise :

            break;
        case MotionTypeEnum::CircularInterpolationCounterClockwise :

            break;

    }

    
        // std::cout << "Moved in MotionType: " << (int)CNCSetup::getMotionType() 
        // << " by X: " << newX << " Y: "<< newY << " Z: " << newZ << " I: " << i << " J: " << j << std::endl;
    // std::cout << "FR x: " << feedrateX << " y: " << feedrateY << " z: " << feedrateZ << std::endl;

}

void CNCSetup::feedrateMoveBy(int deltaX, int deltaY, int deltaZ)
{
    double deltaD = sqrt( pow(deltaX , 2) + pow(deltaY, 2) +  pow(deltaZ, 2));

    double XtoD = deltaX/deltaD;
    double YtoD = deltaY/deltaD;
    double ZtoD = deltaZ/deltaD;

    double feedrateD = this->feedRate;

    double feedrateX = XtoD*feedrateD;
    double feedrateY = YtoD*feedrateD;
    double feedrateZ = YtoD*feedrateD;

    std::thread t1( rotate, std::ref( xAxisMotor ), deltaX, feedrateX );
    std::thread t2( rotate, std::ref( yAxisMotor1 ), deltaY, feedrateY );
    std::thread t3( rotate, std::ref( yAxisMotor2 ), deltaY, feedrateY );
    std::thread t4( rotate, std::ref( zAxisMotor ), deltaZ, feedrateZ );

    t1.join();
    t2.join();
    t3.join();
    t4.join();

}

void CNCSetup::rotate(StepperMotor& motor, double mmDistance, double axisFeedrate)
{

    double microstepsPerRevolution = 200* static_cast<int>(motor.getMicrosteps());
    double revolutionsNeeded = mmDistance/motor.getLinearStep();
    int microstepsNeeded = static_cast<int>( revolutionsNeeded*microstepsPerRevolution );

    double mmPerMicrostep = motor.getLinearStep()/microstepsPerRevolution; //mm/microstep
    double feedratePerMicrosec = axisFeedrate/60/1000000; // mm/microsec

    double microsecsPerMicrostep = mmPerMicrostep / feedratePerMicrosec;
    motor.setStepDelayMicrosec( static_cast<int>( microsecsPerMicrostep ));

    for(int i = 0; i < microstepsNeeded; i++)
        motor.step();


}


int CNCSetup::programStop()
{
    std::cout << "Program Stopped By M0 command" << std::endl;
    return 0;
}

int CNCSetup::programPause()
{
    std::string userInput("");
    std::cout << "Program paused\n enter: "; 
    std::cin >> userInput;
    return 0;
}

MotionTypeEnum CNCSetup::getMotionType()
{
    return motionType;
}

int CNCSetup::setMotionPlane( MotionPlane motionPlane )
{
    std::cout << "motion plane mode set to " << static_cast<int>(motionPlane) << std::endl;
    this->motionPlane = motionPlane;
    return 0;  
}

MotionPlane CNCSetup::getMotionPlane()
{
    return motionPlane;
}

int CNCSetup::setFeedMode( FeedMode feedMode )
{
    this->feedMode = feedMode;
    std::cout << "feedMode set to " << static_cast<int>(feedMode) << std::endl;
    return 0;
}

FeedMode CNCSetup::getFeedMode()
{
    return feedMode;
}

int CNCSetup::setUnits( Units units )
{
    std::cout << "units set to " << static_cast<int>(units) << std::endl;
    this->units = units;
    return 0;
}

Units CNCSetup::getUnits()
{
    return units;
}

int CNCSetup::setDistanceMode( DistanceMode distanceMode )
{
    std::cout << "distance mode set to " << static_cast<int>(distanceMode) << std::endl;
    this->distanceMode = distanceMode;
    return 0;
}

DistanceMode CNCSetup::getDistanceMode()
{
    return distanceMode;
}

int CNCSetup::setArcDistanceMode( ArcDistanceMode arcDistanceMode )
{
    std::cout << "arc distance mode set to " << static_cast<int>(arcDistanceMode) << std::endl;
    this->arcDistanceMode = arcDistanceMode;
    return 0;
}

ArcDistanceMode CNCSetup::getArcDistanceMode()
{
    return arcDistanceMode;
}

int CNCSetup::setPathMode( PathMode pathMode, std::vector< GCodeCommand >& command_line )
{
    this->pathMode = pathMode;
    std::cout << "path mode set to: " << static_cast<int>(pathMode);
    if( pathMode == PathMode::Blending )
    {
        for( int i = 0; i < command_line.size(); i++)
        {
            if( command_line[i].getCommandType() == 'P')
            {
                this->pathMode_P = command_line[i].getCommandValue();
                command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            }
        }

        for( int i = 0; i < command_line.size(); i++)
        {
            if( command_line[i].getCommandType() == 'Q')
            {
                this->pathMode_Q = command_line[i].getCommandValue();
                command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            }
        }

        std::cout << " with P: " << pathMode_P << " and Q: " << pathMode_Q << std::endl;
    }
    std::cout << "\n";


    return 0;

}

PathMode getPathMode();


int CNCSetup::setNewTool( double newToolId )
{
    Tool newTool(newToolId);
    this->currentTool = newTool;
    std::cout << "tool set: " << currentTool.getToolId() << std::endl;
    return 0;
}

Tool CNCSetup::getTool()
{
    return currentTool;
}

int CNCSetup::toolChange()
{
    std::cout << "change tool to " << currentTool.getToolId() << std::endl;
    return 0;
}

int CNCSetup::setSpindleState( SpindleState spindleState,  std::vector<GCodeCommand>& command_line)
{
    int letters_used = 0;
    if( spindleState == SpindleState::ONClockwise || spindleState == SpindleState::ONCounterClockwise )
    {
        for(int i = 0; i < command_line.size(); i++)
        {
            if( command_line[i].getCommandType() == 'S' )
            {
                command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
                letters_used++;
                setSpindleSpeed( command_line[i].getCommandValue() );
            }
        }
    }
    else if( spindleState == SpindleState::OFF )
    {

    }


    std::cout << "spindle set to:  " << static_cast<int>(spindleState) << std::endl;
    this->spindleState = spindleState;
    return letters_used;
}

SpindleState CNCSetup::getSpindleState()
{
    return spindleState;
}

int CNCSetup::setSpindleSpeed( double speed)
{
    this->spindleSpeed = speed;
    std::cout << "spindle speed set to " << this->spindleSpeed << std::endl;
    return 0;
}
double CNCSetup::getSpindleSpeed()
{
    return spindleSpeed;
}

int CNCSetup::setToolLengthOffset( std::vector< GCodeCommand >& command_line )
{
    int letters_used = 0;
    int H = 0;
    for(int i = 0; i < command_line.size(); i++)
    {
        if(command_line[i].getCommandType() == 'H')
        {
            H = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            letters_used++;
        }
    }
    this->toolLengthOffset = H;
    return letters_used;
}

int CNCSetup::cancelToolLengthOffset()
{
    this->toolLengthOffset = 0;
    return 0;
}

double CNCSetup::getToolLengthOffset()
{
    return this->toolLengthOffset;
}