#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>

class LedControl {
    public:
        LedControl();
        void almostDawn();
        void almostDawnAfter30Minutes();
        void beforeTimeForSleep();
        void turnOffAllLed();

        // Getter
        int getRed();
        int getGreen();
        int getBlue();
    private:
        int red;
        int green;
        int blue;
};

#endif