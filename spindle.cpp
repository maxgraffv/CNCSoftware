#include "spindle.h"
#include "MotorRotationDirectionEnum.h"

Spindle::Spindle( int pwm_pin, int dir_pin):pwm_pin(pwm_pin), dir_pin(dir_pin)
{
    std::cout << "Spindle created id: " << getId() << std::endl;
}

Spindle::~Spindle()
{
    std::cout << "Spindle destroyed id: " << getId() << std::endl;
}

void Spindle::setSpeed(double speed)
{

} 

double Spindle::getSpeed()
{
    return getSpeed();
}

void Spindle::setDirection( MotorRotationDirection direction)
{

}

MotorRotationDirection Spindle::getDirection()
{
    return getDirection();
}


void Spindle::setToolLen(double toolLen)
{
    this->toolLen = toolLen;
}

double Spindle::getToolExtLen()
{
    return this->toolLen;
}

void Spindle::setTemp(double temp)
{
    this->temp = temp;
}

double Spindle::getTemp()
{
    return this->temp;
}

void Spindle::setTempMax(double temp_max)
{
    this->temp_max = temp_max;
}

double Spindle::getTempMax()
{
    return this->temp_max;
}


