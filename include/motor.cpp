#include <iostream>
#include "motor.h"
#include "axisEnum.h"
#include "MotorRotationDirectionEnum.h"


int Motor::counter = 0;

Motor::Motor() : id(counter++), speed(0)
{
    // std::cout << "Motor created id: "<< id << std::endl;
}

Motor::~Motor()
{
    // std::cout << "Motor destroyed id: " << id << std::endl;
}

int Motor::getId()
{
    return id;
}

void Motor::setSpeed(double speed)
{
    this->speed = speed;
}

double Motor::getSpeed()
{
    return this->speed;
}

void Motor::setDirection( MotorRotationDirection direction )
{
    this->motorRotationDirection = direction;
}

MotorRotationDirection Motor::getDirection()
{
    return this->motorRotationDirection;
}

