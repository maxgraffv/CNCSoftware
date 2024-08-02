#ifndef WIRING_MAC_H
#define WIRING_MAC_H

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

int wiringPiSetup();
void pinMode(int a, int b);
void digitalWrite(int a, int b);
void delayMicroseconds(double microsec);
void pullUpDnControl(int a, int b);

void pwmSetMode(int val);   // Use mark-space mode
void pwmSetRange(int val);         // Set the range (0 to 1023)
void pwmSetClock(int val);           // Set the PWM frequency

void pwmWrite(int pwm_pin,int val);  


#endif