#ifndef SPINDLE_H
#define SPINDLE_H

#include "motor.h"
#include "MotorRotationDirectionEnum.h"

#ifdef __APPLE__
    #include "wiringMac.h"
#else
    #include <wiringPi.h>
#endif

class Spindle : public Motor
{

    private:
        int pwm_pin;
        int dir_pin;

        double toolLen; //milimeters
        double temp;
        double temp_max;

    public:

        Spindle(int pwm_pin, int dir_pin);
        virtual ~Spindle();

        void setSpeed(double speed) override;
        double getSpeed() override;
        void setDirection( MotorRotationDirection ) override;
        MotorRotationDirection getDirection() override;

        void setToolLen(double toolLen);
        double getToolExtLen();
        void setTemp(double temp);
        double getTemp();
        void setTempMax(double tempMax);
        double getTempMax();
        






};

#endif