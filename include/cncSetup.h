#ifndef CNC_SETUP_H
#define CNC_SETUP_H

#include <vector>
#include "stepperMotor.h"
#include "spindle.h"
#include "unitsEnum.h"
#include "gcodeFile.h"
#include "motionTypeEnum.h"
#include "motionPlaneEnum.h"
#include "feedMode.h"
#include "distanceMode.h"
#include "arcDistanceMode.h"
#include "spindleState.h"
#include "Tool.h"
#include "pathMode.h"
#include <thread>
#include <functional>
#include "CoordinateSystem.h"
#include <set>
#include "LimitSwitch.h"


class CNCSetup
{

    private:
        StepperMotor xAxisMotor;
        StepperMotor yAxisMotor1;
        StepperMotor yAxisMotor2;
        StepperMotor zAxisMotor;
        Spindle spindle;

        LimitSwitch limitSwitchX;
        LimitSwitch limitSwitchY;
        LimitSwitch limitSwitchZ;
        LimitSwitch limitSwitchT;

        Units units;

        double absolutePosX;
        double absolutePosY;
        double absolutePosZ;
        CoordinateSystem currentCoordinates;

        CoordinateSystem machineCoordinates;
        std::set< CoordinateSystem > coordinateSystems_set;

        double feedRate;
        double feedRateMax;
        Tool currentTool;

        MotionTypeEnum motionType;
        MotionPlane motionPlane;
        FeedMode feedMode;
        DistanceMode distanceMode;
        ArcDistanceMode arcDistanceMode;
        PathMode pathMode;




        SpindleState spindleState;
        double spindleSpeed;
        double toolLengthOffset;



    public:
        CNCSetup(
            StepperMotor& xAxisMotor,
            StepperMotor& yAxisMotor1,
            StepperMotor& yAxisMotor2,
            StepperMotor& zAxisMotor,
            Spindle& spindle,
            LimitSwitch& lSwitchX,
            LimitSwitch& lSwitchY,
            LimitSwitch& lSwitchZ,
            LimitSwitch& lSwitchT,
            Units units );

        void setXAxisMotor( StepperMotor& xAxisMotor );
        void setYAxisMotor( StepperMotor& xAxisMotor );
        void setZAxisMotor( StepperMotor& xAxisMotor );
        void setSpindle( Spindle& spindle );

        std::vector<double> getAbsolutePos();

        void move(double x, double y, double z, std::vector< GCodeCommand >& command_line);

        void linearMove( double X, double Y, double Z, std::vector< GCodeCommand>& command_line);
        void feedrateMoveBy(double feedrate, double deltaX, double deltaY, double deltaZ);
        void rotate(StepperMotor& motor, double mmDistance, double axisFeedrate);

        void arcMove( double X, double Y, double Z, std::vector< GCodeCommand>& command_line);
        void arcMoveTo( double X, double Y, double Z, double I, double J, double K);

        void run( GCodeFile &gcodeFile );
        int execute( std::vector< GCodeCommand >& command_line );

        void process( std::vector< GCodeCommand >& command_line );

        void home();

        int programPause();
        int programStop();

        int setNewTool( double newToolId );
        Tool getTool();

        int setMotionType( MotionTypeEnum motionType, std::vector<GCodeCommand>& command_line );
        MotionTypeEnum getMotionType();

        int setMotionPlane( MotionPlane motionPlane );
        MotionPlane getMotionPlane();
        
        int setFeedRate( double feedRate );
        double getFeedRate();

        int setFeedMode( FeedMode feedMode );
        FeedMode getFeedMode();

        int setUnits( Units units );
        Units getUnits();

        int setDistanceMode( DistanceMode distanceMode );
        DistanceMode getDistanceMode();

        int setArcDistanceMode( ArcDistanceMode arcDistanceMode );
        ArcDistanceMode getArcDistanceMode();

        int setPathMode( PathMode pathMode, std::vector< GCodeCommand >& command_line );
        PathMode getPathMode();
        double pathMode_P;
        double pathMode_Q;

        int setSpindleState( SpindleState spindleState, std::vector<GCodeCommand>& comand_line );
        SpindleState getSpindleState();

        int setSpindleSpeed( double speed);
        double getSpindleSpeed();

        int setToolLengthOffset( std::vector< GCodeCommand >& command_line );
        int cancelToolLengthOffset();
        double getToolLengthOffset();

        int toolChange();

        void setCurrentCoordinateSystem( double coordinateSystemId );


};

bool containsCodeType(std::vector< GCodeCommand > command_vec, char c);

#endif