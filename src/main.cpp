#include "init.h"

void setup() {
  Serial.begin(115200);

  rtc_main.checkStatusDS3231();

  wf_main.connectWifi();

  mqtt_main.connectAWS();

  pinMode(lc_main.getRed(), OUTPUT);
  pinMode(lc_main.getGreen(), OUTPUT);
  pinMode(lc_main.getBlue(), OUTPUT);
  pinMode(hb_main.getButtonPin(), INPUT_PULLUP);
  pinMode(hb_main.getButtonPinDay(), INPUT_PULLUP);
  pinMode(hb_main.getButtonPinTestMode(), INPUT_PULLUP);

  lc_main.turnOffAllLed();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {

  String currentDay = rtc_main.checkDayCurrrent();

  if (currentDay != lastDay) {
    sunriseLocalTime = rtc_main.getSunriseLocalTime();
    Serial.println("Thời gian mặt trời mọc: " + sunriseLocalTime);

    sunsetLocalTime = rtc_main.getSunsetLocalTime();
    Serial.println("Thời gian mặt trời lặn: " + sunsetLocalTime);

    sunsetLocalTimeAfter30Minutes = rtc_main.getSunsetLocalTimeAfter30Minutes();
    Serial.println("Thời gian mặt trời lặn sau 30': " + sunsetLocalTimeAfter30Minutes);


    sunriseLocalTimeSeconds = rtc_main.convertToSeconds(sunriseLocalTime);
    sunsetLocalTimeSeconds = rtc_main.convertToSeconds(sunsetLocalTime);
    sunsetLocalTimeAfter30MinutesSeconds = rtc_main.convertToSeconds(sunsetLocalTimeAfter30Minutes);
    timeForSleep = rtc_main.convertToSeconds("23:0:0");

    mqtt_main.publishMessageSunriseSunsetLocalTime( sunriseLocalTime, sunsetLocalTime );
    lastDay = currentDay;
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.print(rtc_main.checkDayOfWeek());
  display.print(" ");
  display.print(rtc_main.checkDayCurrrent());
  display.print("/");
  display.print(rtc_main.checkMonthCurrent());
  display.print("/");
  display.print(rtc_main.checkYearCurrent());

  display.drawLine(92, 0, 92, 32, SSD1306_WHITE);

  display.setCursor(0, 15);
  display.setTextSize(2);

  int hour = rtc_main.checkHourCurrent();
  int minute = rtc_main.checkMinuteCurrent();

  if (hour < 10) {
    display.print("0");
  }
  display.print(hour);
  display.print(":");
  if (minute < 10) {
    display.print("0");
  }
  display.print(minute);

  display.drawBitmap(62, 10, cloudy, 24, 24, SSD1306_WHITE);

  int currentTimeSeconds = rtc_main.convertToSeconds(rtc_main.checkTimeCurrent());
  Serial.println("Thời gian hiện tại ( giây ): " + String(currentTimeSeconds));

  int buttonDayMain = hb_main.getButtonPinDay();
  bool currentButtonStateMain = digitalRead(buttonDayMain);

  static unsigned long lastMillisMain = 0;
  unsigned long newMillisMain = millis();

  bool isDayCheck = true;

  if ( newMillisMain - lastMillisMain < 50 ) {

  } else {
      if (currentButtonStateMain != lastButtonStateMain) {
          if (currentButtonStateMain == LOW) {
              countMain += 1;
          }
          lastButtonStateMain = currentButtonStateMain;
      }
      if(countMain % 2 == 1) {
        Serial.println("Button Pressed - Night");
        isDayCheck = false;
      } else {
        Serial.println("Button Pressed - Day");
        isDayCheck = true;
      }
  }

  // currentTimeSeconds < sunsetLocalTimeSeconds && currentTimeSeconds > sunriseLocalTimeSeconds
  if (isDayCheck) {

      hb_main.buttonDay();

      int currentCount = hb_main.getCount();
      
      if (currentCount != previousCount) {
          if (currentCount % 2 == 1) {
            mqtt_main.publishMessageDay("ON");
          } else {
            mqtt_main.publishMessageDay("OFF");
          }
          previousCount = currentCount;
      }

      display.drawBitmap(94, 0, sunset, 32, 32, SSD1306_WHITE);

  } else {

    hb_main.buttonNight(sunriseLocalTimeSeconds, sunsetLocalTimeSeconds, sunsetLocalTimeAfter30MinutesSeconds, timeForSleep, currentTimeSeconds);

    String currentStatus = hl_main.getStatusCheck();
    if (currentStatus != previousStatus) {
      if (currentStatus == "almostDawn") {
        mqtt_main.publishMessageNight("ON", "OFF", "OFF");
      } else if (currentStatus == "almostDawn30minutes") {
        mqtt_main.publishMessageNight("OFF", "ON", "OFF");
      } else if (currentStatus == "beforeSleep") {
        mqtt_main.publishMessageNight("OFF", "OFF", "ON");
      } else if (currentStatus == "sleep") {
        mqtt_main.publishMessageNight("OFF", "OFF", "OFF");
      }
      previousStatus = currentStatus; 
    }

    if (currentStatus == "almostDawn") {
      display.drawBitmap(94, 0, sunset, 32, 32, SSD1306_WHITE);
    } else if (currentStatus == "almostDawn30minutes") {
      display.drawBitmap(94, 0, night, 32, 32, SSD1306_WHITE);
    } else if (currentStatus == "beforeSleep") {
      display.drawBitmap(94, 0, beforeSleep, 32, 32, SSD1306_WHITE);
    } else if (currentStatus == "sleep") {
      display.drawBitmap(94, 0, good_night, 32, 32, SSD1306_WHITE);
    }
  }

  mqtt_main.clientLoop();
  display.display();
  delay(100);
}