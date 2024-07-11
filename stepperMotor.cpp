#include "stepperMotor.h"


StepperMotor::StepperMotor()
{
    std::cout << "Stepper Motor created id: "<< getId() << std::endl;
}

StepperMotor::~StepperMotor()
{
    std::cout << "Stepper Motor destroyed id: "<< getId() << std::endl;
}

void StepperMotor::setSpeed(double speed)
{
    std::cout << "Stepper Motor Speed Set" << std::endl;
} 

double StepperMotor::getSpeed()
{

}

void StepperMotor::setDirection( MotorRotationDirection direction)
{
    std::cout << "Stepper Motor Direction Set" << std::endl;
}

MotorRotationDirection StepperMotor::getDirection()
{

}

void StepperMotor::rotate()
{
    std::cout << "Motor Rotating" << std::endl;
}

