#include "LimitSwitch.h"

LimitSwitch::LimitSwitch(int pin)
{
    this->pin = pin;
}

int LimitSwitch::getPin()
{
    return pin;
}