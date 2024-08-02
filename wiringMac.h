#ifndef WIRING_MAC_H
#define WIRING_MAC_H

int wiringPiSetup();
void pinMode(int a, int b);
void digitalWrite(int a, int b);
void delayMicroseconds(double microsec);
void pullUpDnControl(int a, int b);



#endif