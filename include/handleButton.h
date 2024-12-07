#ifndef HANDLEBUTTON_H
#define HANDLEBUTTON_H

#include <Arduino.h>
#include <ledControl.h> // Use variable LED1, LED2 and LED3
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class HandleButton {
    public:
        HandleButton();
        void buttonDay();
        void buttonNight(int sunriseLocalTimeSeconds, int sunsetLocalTimeSeconds, int sunsetLocalTimeAfter30Minutes, int timeForSleep, int currentTimeSeconds);
        int getButtonPin();
        void setButtonPin(int pin);
        int getCount();
        int getButtonPinDay();
        int getButtonPinTestMode();
    private:
        int buttonState;
        int buttonPin;
        int buttonPinTestMode;
        int buttonPinDay;
    };
#endif
