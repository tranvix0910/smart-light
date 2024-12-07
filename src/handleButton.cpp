#include "handleButton.h"
#include "handleLed.h"
#include "ledControl.h"

bool lastButtonState = HIGH;
int count = 0;

bool lastButtonStateTestMode = HIGH;
int countTestMode = 0;

LedControl lc_hb;
HandleLed hl_hb;

HandleButton::HandleButton() : buttonPin(12), buttonPinTestMode(27), buttonPinDay(14) {
    buttonState = LOW;
}

void HandleButton::buttonDay(){

    static unsigned long lastMillis = 0;
    unsigned long newMillis = millis();

    bool currentButtonState = digitalRead(buttonPin);

    if ( newMillis - lastMillis < 50 ) {

    } else {
        if (currentButtonState != lastButtonState) {
            if (currentButtonState == LOW) {
                count += 1;
            }
            lastButtonState = currentButtonState;
        }
        if(count % 2 == 1) {
            Serial.println("Button Pressed - Turn On Led 2");
            analogWrite(lc_hb.getRed(), 255);
            analogWrite(lc_hb.getGreen(), 255);
            analogWrite(lc_hb.getBlue(), 200);
        } else {
            Serial.println("Button Pressed - Turn Off Led 2");
            analogWrite(lc_hb.getRed(), 0);
            analogWrite(lc_hb.getGreen(), 0);
            analogWrite(lc_hb.getBlue(), 0);
        }
    }
}

void HandleButton::buttonNight(int sunriseLocalTimeSeconds, int sunsetLocalTimeSeconds, int sunsetLocalTimeAfter30Minutes, int timeForSleep, int currentTimeSeconds) {

    static unsigned long lastMillis = 0;
    unsigned long newMillis = millis();

    bool currentButtonState = digitalRead(buttonPin);
    bool currentButtonStateTestMode = digitalRead(buttonPinTestMode);

    if ( newMillis - lastMillis < 50 ) {

    } else {
        if (currentButtonState != lastButtonState) {
            if (currentButtonState == LOW) {
                count += 1;
            }
            lastButtonState = currentButtonState;
        }
        if(count % 2 == 1) {
            Serial.println("Button Pressed - Turn Off All Led");
            lc_hb.turnOffAllLed();
        } else {
            Serial.println("Button Pressed - Handle Led Night");
            Serial.println("Count Test Mode: " + String(countTestMode));
            if (currentButtonStateTestMode != lastButtonStateTestMode) {
                if (currentButtonStateTestMode == LOW) {
                    countTestMode += 1;
                }
                lastButtonStateTestMode = currentButtonStateTestMode;
            }
            if(countTestMode % 2 == 1) {
                Serial.println("Button Pressed - Test Mode");
                hl_hb.handleNightLEDTestMode();
            } else {
                Serial.println("Button Pressed - Realtime Mode");
                hl_hb.handleNightLEDRealTimeMode(sunriseLocalTimeSeconds, sunsetLocalTimeSeconds, sunsetLocalTimeAfter30Minutes, timeForSleep, currentTimeSeconds);
            }
        }
        
        
    }
} 

int HandleButton::getButtonPin() {
    return buttonPin;
}

int HandleButton::getButtonPinDay() {
    return buttonPinDay;
}

int HandleButton::getButtonPinTestMode() {
    return buttonPinTestMode;
}

void HandleButton::setButtonPin(int pin) {
    buttonPin = pin;
}

int HandleButton::getCount() {
    return count;
}

