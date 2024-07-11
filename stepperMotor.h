#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include "axisEnum.h"
#include "motor.h"
#include "microstepResolutionEnum.h"

class StepperMotor : public Motor
{
    private:
        Axis axis;
        MicrostepResolution microstepResolution;



    public:
        StepperMotor();
        virtual ~StepperMotor();
        
        void setSpeed(double speed) override;
        double getSpeed() override;
        void setDirection( MotorRotationDirection ) override;
        MotorRotationDirection getDirection() override;
        void rotate() override;

};

#endif