#ifndef MOTOR_H
#define MOTOR_H

#include <iostream>
#include "MotorRotationDirectionEnum.h"

class Motor
{
    private:
        static int counter;
        int id;
        double speed; // Revolutions per sec
        MotorRotationDirection motorRotationDirection;
        

    public:
        Motor();
        virtual ~Motor();
        int getId();

        virtual void setSpeed(double speed) = 0;
        virtual double getSpeed() = 0;

        virtual void setDirection( MotorRotationDirection direction ) = 0;
        virtual MotorRotationDirection getDirection() = 0;

};

#endif // MOTOR_H

