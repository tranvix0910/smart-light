#include "handleLed.h"
#include "ledControl.h"
#include "rtc.h"

LedControl lc_hl;
RTC rtc_hl;

HandleLed::HandleLed(){
  nightStartTime = 0;
  currentMillis = 0;
  isInitialCheckDone = false;
}

String statusCheck = "almostDawn";
LightState currentLightState = STATE_ALMOST_DAWN;

void HandleLed::handleNightLEDTestMode(){

  unsigned long additionalTime = rtc_hl.getTimeCollectAPI();
  currentMillis = millis() - additionalTime;

  switch (currentLightState) {
    case STATE_ALMOST_DAWN:
      // if(convertToSeconds(checkTimeCurrent()) > convertToSeconds(sunsetLocalTime) && convertToSeconds(checkTimeCurrent()) < convertToSeconds(sunsetLocalTimeAffter30minutes)){
      lc_hl.almostDawn();
      if(currentMillis - nightStartTime >= 5000){
        nightStartTime = currentMillis;
        currentLightState = STATE_ALMOST_DAWN_30_MINUTES;
        statusCheck = "almostDawn30minutes";
      }
      break;
    case STATE_ALMOST_DAWN_30_MINUTES:
      lc_hl.almostDawnAfter30Minutes();
      // if (convertToSeconds(checkTimeCurrent()) > convertToSeconds(sunsetLocalTimeAffter30minutes) && convertToSeconds(checkTimeCurrent()) < convertToSeconds("21:50:0")) {
      if(currentMillis - nightStartTime >= 5000){
        // Serial.println("currentMillis - nightStartTime ( STATE_ALMOST_DAWN ): " + String(currentMillis) + "--" + String(nightStartTime));
        currentLightState = STATE_BEFORE_SLEEP;
        nightStartTime = currentMillis;
        statusCheck = "beforeSleep";
      }
      // }
      break;

    case STATE_BEFORE_SLEEP:
      lc_hl.beforeTimeForSleep();
      // if (convertToSeconds(checkTimeCurrent()) > convertToSeconds("21:50:0") && convertToSeconds(checkTimeCurrent()) > convertToSeconds("22:0:0")) {
        if(currentMillis - nightStartTime >= 5000){          
          currentLightState = STATE_SLEEP;
          nightStartTime = currentMillis;
          statusCheck = "sleep";
        }
      // }
      break;
    case STATE_SLEEP:
      lc_hl.turnOffAllLed();
      if (currentMillis - nightStartTime >= 5000) {
        // Serial.println("currentMillis - nightStartTime ( STATE_BEFORE_SLEEP ): " + String(currentMillis) + "--" + String(nightStartTime));  
        currentLightState = STATE_ALMOST_DAWN;
        nightStartTime = currentMillis;
        statusCheck = "almostDawn";
      }
  }
}

void HandleLed::handleNightLEDRealTimeMode(int sunriseLocalTimeSeconds, int sunsetLocalTimeSeconds, int sunsetLocalTimeAfter30MinutesSeconds, int timeForSleep, int currentTimeSeconds){

  if (!isInitialCheckDone) {
    if(currentTimeSeconds >= 0 && currentTimeSeconds < sunriseLocalTimeSeconds){
      if(currentTimeSeconds + 86400 > timeForSleep && currentTimeSeconds < sunriseLocalTimeSeconds){
        statusCheck = "sleep";
        currentLightState = STATE_SLEEP;
      }
    } else {
      if(currentTimeSeconds > sunsetLocalTimeSeconds && currentTimeSeconds < sunsetLocalTimeAfter30MinutesSeconds){
        statusCheck = "almostDawn";
        currentLightState = STATE_ALMOST_DAWN;
      } else if(currentTimeSeconds > sunsetLocalTimeAfter30MinutesSeconds && currentTimeSeconds < timeForSleep - 900){
        statusCheck = "almostDawn30minutes";
        currentLightState = STATE_ALMOST_DAWN_30_MINUTES;
      } else if (currentTimeSeconds > timeForSleep - 900 && currentTimeSeconds < timeForSleep){
        statusCheck = "beforeSleep";
        currentLightState = STATE_BEFORE_SLEEP;
      } else {
        statusCheck = "sleep";
        currentLightState = STATE_SLEEP;
      }
    }
    isInitialCheckDone = false;
  }
  
  switch (currentLightState) {
    case STATE_ALMOST_DAWN:
      // if(convertToSeconds(checkTimeCurrent()) > convertToSeconds(sunsetLocalTime) && convertToSeconds(checkTimeCurrent()) < convertToSeconds(sunsetLocalTimeAffter30minutes)){
      lc_hl.almostDawn();
      // currentTimeSeconds > sunriseLocalTimeSeconds && currentTimeSeconds < sunsetLocalTimeAfter30MinutesSeconds
      if(currentTimeSeconds > sunsetLocalTimeAfter30MinutesSeconds && currentTimeSeconds < timeForSleep - 900){
        nightStartTime = currentMillis;
        currentLightState = STATE_ALMOST_DAWN_30_MINUTES;
        statusCheck = "almostDawn30minutes";
      }
      break;
    case STATE_ALMOST_DAWN_30_MINUTES:
      lc_hl.almostDawnAfter30Minutes();
      // if (convertToSeconds(checkTimeCurrent()) > convertToSeconds(sunsetLocalTimeAffter30minutes) && convertToSeconds(checkTimeCurrent()) < convertToSeconds("21:50:0")) {
      if(currentTimeSeconds > timeForSleep - 900 && currentTimeSeconds < timeForSleep){
        // Serial.println("currentMillis - nightStartTime ( STATE_ALMOST_DAWN ): " + String(currentMillis) + "--" + String(nightStartTime));
        currentLightState = STATE_BEFORE_SLEEP;
        nightStartTime = currentMillis;
        statusCheck = "beforeSleep";
      }
      // }
      break;

    case STATE_BEFORE_SLEEP:
      lc_hl.beforeTimeForSleep();
      // if (convertToSeconds(checkTimeCurrent()) > convertToSeconds("21:50:0") && convertToSeconds(checkTimeCurrent()) > convertToSeconds("22:0:0")) {
        if(currentTimeSeconds > timeForSleep && currentTimeSeconds < 86400){          
          currentLightState = STATE_SLEEP;
          nightStartTime = currentMillis;
          statusCheck = "sleep";
        }
      // }
      break;
    case STATE_SLEEP:
      lc_hl.turnOffAllLed();
      // if (currentTimeSeconds > sunsetLocalTimeSeconds && currentTimeSeconds < sunsetLocalTimeAfter30MinutesSeconds) {
      //   // Serial.println("currentMillis - nightStartTime ( STATE_BEFORE_SLEEP ): " + String(currentMillis) + "--" + String(nightStartTime));  
      //   currentLightState = STATE_ALMOST_DAWN;
      //   nightStartTime = currentMillis;
      //   statusCheck = "almostDawn";
      // }
  }
}

String HandleLed::getStatusCheck() {
  return statusCheck;
}

bool HandleLed::isDayTime(){
  return false;
}

