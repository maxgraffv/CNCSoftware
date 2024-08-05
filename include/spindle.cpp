#include "spindle.h"
#include "MotorRotationDirectionEnum.h"



Spindle::Spindle( int pwm_pin, int dir_pin):pwm_pin(pwm_pin), dir_pin(dir_pin)
{
    // std::cout << "Spindle created id: " << getId() << std::endl;
    pinMode(pwm_pin, PWM_OUTPUT);  // Set GPIO18 as PWM output
    pinMode(dir_pin, OUTPUT);  // Set GPIO18 as PWM output

    // Set the PWM mode and range
    pwmSetMode(PWM_MODE_MS);   // Use mark-space mode
    pwmSetRange(1024);         // Set the range (0 to 1023)
    pwmSetClock(32);           // Set the PWM frequency

    // Generate a PWM signal with a 50% duty cycle
    pwmWrite(pwm_pin, 0);     




}

Spindle::~Spindle()
{
    // std::cout << "Spindle destroyed id: " << getId() << std::endl;
}

void Spindle::setSpeed(double speed)
{
    double maxRPM = 12000;
    double RPMproportion = speed/maxRPM;

    int pwmValue = static_cast<int>( RPMproportion*1023 );
    pwmWrite(pwm_pin, pwmValue);
    Motor::setSpeed(speed);
} 

double Spindle::getSpeed()
{
    return Motor::getSpeed();
}

void Spindle::setDirection( MotorRotationDirection direction)
{
    switch(direction)
    {
        case MotorRotationDirection::CLOCKWISE :
            digitalWrite(dir_pin, LOW);
            break;
        case MotorRotationDirection::ANTICLOCKWISE :
            digitalWrite(dir_pin, HIGH);
    }
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


