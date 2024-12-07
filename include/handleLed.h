#ifndef HANDLE_LED_H
#define HANDLE_LED_H

#include <Arduino.h>
#include "ledControl.h"

enum LightState {
  STATE_ALMOST_DAWN,
  STATE_ALMOST_DAWN_30_MINUTES,
  STATE_BEFORE_SLEEP,
  STATE_SLEEP
};

extern LightState currentLightState;

class HandleLed {
  public:
    HandleLed();
    void handleNightLEDTestMode();
    void handleNightLEDRealTimeMode(int sunriseLocalTimeSeconds, int sunsetLocalTimeSeconds, int sunsetLocalTimeAfter30MinutesSeconds, int timeForSleep, int currentTimeSeconds);
    bool isDayTime();
    String getStatusCheck();
  private:
    unsigned long nightStartTime;
    unsigned long currentMillis;
    bool isInitialCheckDone;
};

#endif