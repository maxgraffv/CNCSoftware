#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include "axisEnum.h"
#include "motor.h"
#include "microstepResolutionEnum.h"

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OUTPUT 1
#define INPUT 0
#define LOW 0
#define HIGH 1


class StepperMotor : public Motor
{
    private:
        int step_pin, dir_pin, en_pin, ms2_pin, ms1_pin;
        MicrostepResolution microstepResolution;
        MotorRotationDirection rotationDirection;
        double speed;
        double stepDelay_microsec;

        /*
            ms2 ms1 microstep        
            GND GND     8  | YES it's 8
            VCC VCC     16 | YES it's 16
            GND VCC     2 | nope it's actually 32
            VCC GND     4 | nope its actually 64
        */

    public:
        StepperMotor(int step_pin, int dir_pin, int en_pin, int ms1_pin, int ms2_pin, MicrostepResolution MicrostepResolution, MotorRotationDirection rotationDirection);
        virtual ~StepperMotor();
        
        void enable();
        void disable();

        void setSpeed(double speed) override;
        double getSpeed() override;
    
        void setMicrosteps( MicrostepResolution microsteps);
        MicrostepResolution getMicrosteps();

        void setDirection( MotorRotationDirection ) override;
        MotorRotationDirection getDirection() override;

        void setStepDelayMicrosec( double microseconds );
        double getStepDelayMicrosec();

        void step();

};

#endif