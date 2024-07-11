#ifndef SPINDLE_H
#define SPINDLE_H

#include "motor.h"

class Spindle : public Motor
{

    private:
        double toolLen; //milimeters
        double temp;
        double temp_max;

    public:

        Spindle();
        virtual ~Spindle();

        void setSpeed(double speed) override;
        double getSpeed() override;
        void setDirection( MotorRotationDirection ) override;
        MotorRotationDirection getDirection() override;
        void rotate() override;

        void setToolLen(double toolLen);
        double getToolExtLen();
        void setTemp(double temp);
        double getTemp();
        void setTempMax(double tempMax);
        double getTempMax();






};

#endif