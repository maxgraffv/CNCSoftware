#include "stepperMotor.h"

#include <wiringPi.h>
#include "MotorRotationDirectionEnum.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


StepperMotor::StepperMotor(int step_pin, int dir_pin, int en_pin, 
    int ms1_pin, int ms2_pin, 
    MicrostepResolution microstepResolution, 
    MotorRotationDirection rotationDirection)
:step_pin(step_pin), dir_pin(dir_pin), en_pin(en_pin), 
ms1_pin(ms1_pin), ms2_pin(ms2_pin), 
microstepResolution(microstepResolution),
rotationDirection(rotationDirection)
{
    // Setup wiringPi
    if (wiringPiSetup() == -1) {
        printf("wiringPi setup failed\n");
        exit(1);
    }

    // Set pin modes
    pinMode(step_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    pinMode(en_pin, OUTPUT);
    pinMode(ms1_pin, OUTPUT);
    pinMode(ms2_pin, OUTPUT);

    enable();

    setMicrosteps( microstepResolution );
}

StepperMotor::~StepperMotor()
{
    // std::cout << "Stepper Motor destroyed id: "<< getId() << std::endl;
}

void StepperMotor::enable()
{
    digitalWrite(en_pin, LOW); // Enable pin active LOW
}

void StepperMotor::disable()
{
    digitalWrite(en_pin, HIGH); // Disable pin active HIGH
}

void StepperMotor::setSpeed(double speed)
{
    std::cout << "Stepper Motor Speed Set" << std::endl;
} 

double StepperMotor::getSpeed()
{
    return speed;
}

void StepperMotor::setMicrosteps( MicrostepResolution microsteps)
{
    switch(microsteps)
    {
        case MicrostepResolution::EIGHTH_STEP :
            digitalWrite(ms1_pin, LOW);
            digitalWrite(ms2_pin, LOW);
            break;
        case MicrostepResolution::SIXTEENTH_STEP :
            digitalWrite(ms1_pin, HIGH);
            digitalWrite(ms2_pin, HIGH);
            break;
        case MicrostepResolution::THIRTY_SECOND_STEP :
            digitalWrite(ms1_pin, HIGH);
            digitalWrite(ms2_pin, LOW);
            break;
        case MicrostepResolution::SIXTY_FOURTH_STEP :
            digitalWrite(ms1_pin, LOW);
            digitalWrite(ms2_pin, HIGH);
            break;
    }
    this->microstepResolution = microsteps;
    std::cout << "Stepper Motor "<<getId() << ": microstep resolution set to " << static_cast<int>( microsteps ) << std::endl;
}

MicrostepResolution StepperMotor::getMicrosteps()
{
    return microstepResolution;
}

void StepperMotor::setDirection( MotorRotationDirection direction)
{
    if( direction == MotorRotationDirection::CLOCKWISE)
    {
        digitalWrite(dir_pin, HIGH);
        std::cout << "Stepper Motor Direction Set Clockwise" << std::endl;
    }
    else
    {
        digitalWrite(dir_pin, LOW);
        std::cout << "Stepper Motor Direction Set Counter Clockwise" << std::endl;
    }
}

MotorRotationDirection StepperMotor::getDirection()
{
    return rotationDirection;
}

void StepperMotor::step()
{
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(stepDelay_microsec);  // Delay for the step
    digitalWrite(step_pin, LOW);
    delayMicroseconds(stepDelay_microsec);  // Delay before next step
}
