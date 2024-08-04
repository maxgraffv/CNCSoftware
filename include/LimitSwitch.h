#ifndef LIMIT_SWITCH_H
#define LIMIT_SWITCH_H

class LimitSwitch
{
    private:

        int pin;

    public:

        LimitSwitch(int pin);
        int getPin();

};



#endif