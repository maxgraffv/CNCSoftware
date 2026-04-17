#include "wiringMac.h"

int wiringPiSetup()
{
    return 0;
}

void pinMode([[maybe_unused]] int a, [[maybe_unused]] int b) {}

void digitalWrite([[maybe_unused]] int a, [[maybe_unused]] int b) {}

int digitalRead([[maybe_unused]] int pin)
{
    return 0;
}

void delayMicroseconds([[maybe_unused]] double microsec) {}

void pullUpDnControl([[maybe_unused]] int a, [[maybe_unused]] int b) {}

void pwmSetMode([[maybe_unused]] int val) {}

void pwmSetRange([[maybe_unused]] int val) {}

void pwmSetClock([[maybe_unused]] int val) {}

void pwmWrite([[maybe_unused]] int pwm_pin, [[maybe_unused]] int val) {}

int wiringPiISR([[maybe_unused]] int a, [[maybe_unused]] int b, [[maybe_unused]] void (*func)(void))
{
    return 0;
}
