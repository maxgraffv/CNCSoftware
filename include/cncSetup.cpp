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
#include "CoordinateSystem.h"
#include "arcPathGenerator.h"
#include "wiringMac.h"





CNCSetup::CNCSetup( 
        StepperMotor& xAxisMotor, StepperMotor& yAxisMotor1,
        StepperMotor& yAxisMotor2, StepperMotor& zAxisMotor,
        Spindle& spindle,
        LimitSwitch& lSwitchX,
        LimitSwitch& lSwitchY,
        LimitSwitch& lSwitchZ,
        LimitSwitch& lSwitchT,
        Units units = Units::milimeter) 
        : xAxisMotor(xAxisMotor), yAxisMotor1(yAxisMotor1),
            yAxisMotor2(yAxisMotor2), zAxisMotor(zAxisMotor),
            spindle(spindle), units(units),
            limitSwitchX(lSwitchX), limitSwitchY(lSwitchY),
            limitSwitchZ(lSwitchZ), limitSwitchT(lSwitchT),
            absolutePosX(0), absolutePosY(0), absolutePosZ(0), 
            arcDistanceMode(ArcDistanceMode::incremental),
            currentTool(0), 
            machineCoordinates(CoordinateSystem(53, 0,0,0)), currentCoordinates( CoordinateSystem(53, 0,0,0) )
{
    feedRateMax = 3000;
    coordinateSystems_set.insert( machineCoordinates );
    currentCoordinates = machineCoordinates;
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
            // std::cout << "Code Line: " << command.getCommandValue() << std::endl;
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

            else if( command.getCommandValue() == 53 )
                CNCSetup::setCurrentCoordinateSystem( 53 );

            else if( command.getCommandValue() >=54 && command.getCommandValue() < 60 )
                CNCSetup::setCurrentCoordinateSystem( command.getCommandValue() );


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
    double X = absolutePosX - currentCoordinates.offsetX;
    double Y = absolutePosY - currentCoordinates.offsetY;
    double Z = absolutePosZ - currentCoordinates.offsetZ;

    int commandLineSize = command_line.size();
    this->motionType = motionType;
    // std::cout << "motion type set to " << static_cast<int>(this->motionType) << std::endl;
    for( int i = 0; i < commandLineSize; i++)
    {
        if(command_line[i].getCommandType() == 'X')
        {
            X = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            letters_used++;
            i--;
            commandLineSize--;
            // std::cout << "X";
        }else

        if(command_line[i].getCommandType() == 'Y')
        {
            Y = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            letters_used++;
            i--;
            commandLineSize--;
            // std::cout << "Y";
        }else

        if(command_line[i].getCommandType() == 'Z')
        {
            Z = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            letters_used++;
            i--;
            commandLineSize--;
            // std::cout << "Z";

        }
    }

    move(X,Y,Z, command_line);

    return letters_used;

}

void CNCSetup::move(double X, double Y, double Z, std::vector< GCodeCommand>& command_line)
{
    switch( motionType )
    {
        case MotionTypeEnum::RapidPositioning :
            linearMove(X,Y,Z,command_line);       
            break;
        case MotionTypeEnum::LinearInterpolation :
            linearMove(X,Y,Z,command_line);       
            break;
        case MotionTypeEnum::CircularInterpolationClockwise :
            arcMove(X,Y,Z,command_line);       
            break;
        case MotionTypeEnum::CircularInterpolationCounterClockwise :
            arcMove(X,Y,Z,command_line);       
            break;
    }
}

void CNCSetup::linearMove( double newX, double newY, double newZ, std::vector< GCodeCommand>& command_line)
{
    int A = 0;
    int B = 0;
    int C = 0;
    int U = 0;
    int V = 0;
    int W = 0;

    int commandLineSize = command_line.size();
    for( int i = 0; i < commandLineSize; i++)
    {
        if(command_line[i].getCommandType() == 'A')
        {
            A = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            i--;
            commandLineSize--;
        }else

        if(command_line[i].getCommandType() == 'B')
        {
            B = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            i--;
            commandLineSize--;
        }else

        if(command_line[i].getCommandType() == 'C')
        {
            C = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            i--;
            commandLineSize--;
        }else
        
        if(command_line[i].getCommandType() == 'U')
        {
            U = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            i--;
            commandLineSize--;
        }else

        if(command_line[i].getCommandType() == 'V')
        {
            V = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            i--;
            commandLineSize--;
        }else

        if(command_line[i].getCommandType() == 'W')
        {
            W = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            i--;
            commandLineSize--;
        }
    }

    double currentX = absolutePosX - currentCoordinates.offsetX;
    double currentY = absolutePosY - currentCoordinates.offsetY;
    double currentZ = absolutePosZ - currentCoordinates.offsetZ;

    double deltaX = 0;
    double deltaY = 0;
    double deltaZ = 0;
    switch( motionType )
    {
        case MotionTypeEnum::RapidPositioning :
            switch( distanceMode )
            {
                case DistanceMode::absoluteDistance :

                    deltaX = newX - currentX;
                    deltaY = newY - currentY;
                    deltaZ = newZ - currentZ;

                    feedrateMoveBy(feedRateMax,deltaX, deltaY, deltaZ);
                    absolutePosX += deltaX;
                    absolutePosY += deltaY;
                    absolutePosZ += deltaZ;
                    break;
                case DistanceMode::incrementalDistance :
                    feedrateMoveBy(feedRateMax, newX, newY, newZ);
                    absolutePosX += newX;
                    absolutePosY += newY;
                    absolutePosZ += newZ;
                    break;
            }
            break;
        case MotionTypeEnum::LinearInterpolation :
            switch( distanceMode )
            {
                case DistanceMode::absoluteDistance :

                    deltaX = newX - currentX;
                    deltaY = newY - currentY;
                    deltaZ = newZ - currentZ;

                    feedrateMoveBy(this->feedRate,deltaX, deltaY, deltaZ);

                    absolutePosX += deltaX;
                    absolutePosY += deltaY;
                    absolutePosZ += deltaZ;

                    break;
                case DistanceMode::incrementalDistance :
                    feedrateMoveBy(this->feedRate, newX, newY, newZ);
                    absolutePosX += newX;
                    absolutePosY += newY;
                    absolutePosZ += newZ;
                    break;
            }
            break;
    }

}

void CNCSetup::arcMove( double X, double Y, double Z, std::vector< GCodeCommand>& command_line)
{

    int I = 0;
    int J = 0;
    int K = 0;
    int R = 0;

    bool isGivenR = false;

    int commandLineSize = command_line.size();
    for( int i = 0; i < commandLineSize; i++)
    {
        if(command_line[i].getCommandType() == 'I')
        {
            I = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            i--;
            commandLineSize--;
        }else

        if(command_line[i].getCommandType() == 'J')
        {
            J = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            i--;
            commandLineSize--;
        }else

        if(command_line[i].getCommandType() == 'K')
        {
            K = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            i--;
            commandLineSize--;
        }else
        
        if(command_line[i].getCommandType() == 'R')
        {
            R = command_line[i].getCommandValue();
            command_line.erase(command_line.begin() + i, command_line.begin()+i+1 );
            i--;
            commandLineSize--;
            isGivenR = true;
        }    
    }

    if( isGivenR == true)
    {
        // CALCULATE I, J, K given R
        std::cout << "R parameter for arc has been given, calculating..." << std::endl;
    }

    arcMoveTo( X, Y, Z, I, J, K );
}

void CNCSetup::arcMoveTo( double absoluteFinalX, double absoluteFinalY, double absoluteFinalZ, double I, double J, double K)
{
    std::vector<ArcPath::Point> arc_vec;

    double X0 = this->absolutePosX - currentCoordinates.offsetX;
    double Y0 = this->absolutePosY - currentCoordinates.offsetY;
    double Z0 = this->absolutePosZ - currentCoordinates.offsetZ;

    switch (getMotionType())
    {
    case MotionTypeEnum::CircularInterpolationClockwise :
        arc_vec = ArcPath::generate( 
            X0, Y0, Z0, 
            absoluteFinalX, absoluteFinalY, absoluteFinalZ,
            I, J, K, CNCSetup::getMotionPlane(), true,
            getArcDistanceMode(), getDistanceMode()
        );
        break;
    
    case MotionTypeEnum::CircularInterpolationCounterClockwise :
        arc_vec = ArcPath::generate( 
            X0, Y0, Z0, 
            absoluteFinalX, absoluteFinalY, absoluteFinalZ,
            I, J, K, CNCSetup::getMotionPlane(), false,
            getArcDistanceMode(), getDistanceMode()
        );
        break;
    }

    double delta_x = 0;
    double delta_y = 0;
    double delta_z = 0;

    for(int i = 0; i < arc_vec.size(); i++)
    {
        
        delta_x = arc_vec[i].x - (absolutePosX - currentCoordinates.offsetX);
        delta_y = arc_vec[i].y - (absolutePosY - currentCoordinates.offsetY);
        delta_z = arc_vec[i].z - (absolutePosZ - currentCoordinates.offsetZ);

        feedrateMoveBy( getFeedRate(), delta_x, delta_y, delta_z );

        absolutePosX += delta_x;
        absolutePosY += delta_y;
        absolutePosZ += delta_z;

    }
}

void CNCSetup::feedrateMoveBy(double feedrate, double deltaX, double deltaY, double deltaZ)
{
    double deltaD = sqrt( pow(deltaX , 2) + pow(deltaY, 2) +  pow(deltaZ, 2));

    double XtoD = deltaX/deltaD;
    double YtoD = deltaY/deltaD;
    double ZtoD = deltaZ/deltaD;

    double feedrateD = feedrate;

    double feedrateX = abs( XtoD*feedrateD );
    double feedrateY = abs( YtoD*feedrateD );
    double feedrateZ = abs( ZtoD*feedrateD );

    std::thread t1( [&]{rotate( xAxisMotor, deltaX, feedrateX); } );
    std::thread t2( [&]{rotate(yAxisMotor1, deltaY, feedrateY);} );
    std::thread t3( [&]{rotate( yAxisMotor2, deltaY, feedrateY);} );
    std::thread t4( [&]{rotate(zAxisMotor, deltaZ, feedrateZ);} );

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // std::cout << "Moved in MotionType: " << (int)CNCSetup::getMotionType() 
    // << " by X: " << deltaX << " Y: "<< deltaY << " Z: " << deltaZ << std::endl;
    // std::cout << "FR x: " << feedrateX << " y: " << feedrateY << " z: " << feedrateZ << std::endl;
    std::cout << "x" << absolutePosX << "y" << absolutePosY << "z" << absolutePosZ << std::endl;

}

void CNCSetup::rotate(StepperMotor& motor, double mmDistance, double axisFeedrate)
{
    if(mmDistance < 0)
    {
        mmDistance = abs( mmDistance );
        motor.setDirection( MotorRotationDirection::ANTICLOCKWISE );
    }

    double microstepsPerRevolution = 200* static_cast<int>(motor.getMicrosteps());
    // std::cout << "motor id " << motor.getId() << " msteps/rev: " << microstepsPerRevolution << std::endl;
    double revolutionsNeeded = mmDistance/motor.getLinearStep();
    // std::cout << "motor id " << motor.getId() << " revs needed: " << revolutionsNeeded << std::endl;
    int microstepsNeeded = static_cast<int>( revolutionsNeeded*microstepsPerRevolution );
    // std::cout << "motor id " << motor.getId() << " msteps needed: " << microstepsNeeded << std::endl;

    double mmPerMicrostep = motor.getLinearStep()/microstepsPerRevolution; //mm/microstep
    // std::cout << "motor id " << motor.getId() << " mm/mstep: " << mmPerMicrostep << std::endl;
    double feedratePerMicrosec = axisFeedrate/60/1000000; // mm/microsec
    // std::cout << "motor id " << motor.getId() << " f-rate/msec: " << feedratePerMicrosec << std::endl;

    double microsecsPerMicrostep = mmPerMicrostep / feedratePerMicrosec;

    // std::cout << "motor id " << motor.getId() << " msec/mstep: " << microsecsPerMicrostep << std::endl;

    motor.setStepDelayMicrosec( static_cast<int>( microsecsPerMicrostep/2 ));

    // std::cout << "step going...";
    for(int i = 0; i < microstepsNeeded; i++)
        motor.step();

    // std::cout << " step done."<<std::endl;

    motor.setDirection( MotorRotationDirection::CLOCKWISE );

}

int CNCSetup::programStop()
{
    std::cout << "Program Stopping..." << std::endl;
    xAxisMotor.disable();
    yAxisMotor1.disable();
    yAxisMotor2.disable();
    zAxisMotor.disable();
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

PathMode CNCSetup::getPathMode()
{
    return pathMode;
}

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

void CNCSetup::setCurrentCoordinateSystem( double coordinateSystemId)
{
    bool containsSystem = false;
    for(auto it = coordinateSystems_set.begin(); it != coordinateSystems_set.end(); it++)
    {
        if( it->Id == coordinateSystemId )
        {
            containsSystem = true;
            currentCoordinates = *it;
            break;
        }
    }

    if( !containsSystem )
    {
        double newOffsetX = 0;
        double newOffsetY = 0;
        double newOffsetZ = 0;

        std::cout << "New Coordinate System is being created..." << std::endl;
        std::cout << "Coordinate System "<< coordinateSystemId << std::endl;
        std::cout << "insert Offset X: "; std::cin >> newOffsetX; std::cout << std::endl;
        std::cout << "insert Offset Y: "; std::cin >> newOffsetY; std::cout << std::endl;
        std::cout << "insert Offset Z: "; std::cin >> newOffsetZ; std::cout << std::endl;

        // newOffsetX = 70;
        // newOffsetY = 150;
        // newOffsetZ = 120;
        
        CoordinateSystem newCoordinateSystem( coordinateSystemId, newOffsetX, newOffsetY, newOffsetZ );

        coordinateSystems_set.insert(newCoordinateSystem);

        currentCoordinates = newCoordinateSystem;
    }
}



void CNCSetup::home()
{
    int x = 1;

    pinMode(limitSwitchX.getPin(), INPUT);
    pullUpDnControl(limitSwitchX.getPin(), PUD_DOWN);

    while( x != 0)
    {
        rotate(xAxisMotor, 0.04, 8000);
        if( wiringPiISR(limitSwitchX.getPin(), INT_EDGE_RISING, x = 0 ) )
        {
            std::cerr << "ISR Failed" << std::endl;
        }


    }




}