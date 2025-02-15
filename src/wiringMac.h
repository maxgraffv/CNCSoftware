#ifndef WIRING_MAC_H
#define WIRING_MAC_H

#include <functional>

#define INPUT 0
#define OUTPUT 1
#define PWM_OUTPUT 2
#define GPIO_CLOCK 3
#define SOFT_PWM_OUTPUT 4
#define SOFT_TONE_OUTPUT 5
#define PWM_TONE_OUTPUT 6

#define LOW 0
#define HIGH 1

#define PUD_OFF 0
#define PUD_DOWN 1
#define PUD_UP 2

#define PWM_MODE_MS 0
#define PWM_MODE_BAL 1

#define INT_EDGE_SETUP 0
#define INT_EDGE_RISING 1
#define INT_EDGE_FALLING 2
#define INT_EDGE_BOTH 3

int wiringPiSetup();
void pinMode(int a, int b);
void digitalWrite(int a, int b);
int digitalRead(int pin);
void delayMicroseconds(double microsec);
void pullUpDnControl(int a, int b);

void pwmSetMode(int val); 
void pwmSetRange(int val);
void pwmSetClock(int val);
void pwmWrite(int pwm_pin,int val);  

int wiringPiISR(int a, int b, void (*func)(void) );


#endif