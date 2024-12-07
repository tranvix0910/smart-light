#include "rtc.h"

char daysOfTheWeekRTC[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

RTC::RTC(){
  url = "https://api.sunrise-sunset.org/json?lat=10.762622&lng=106.660172&formatted=0"; 
  timezoneOffset = 7 * 3600;
  sunsetLocalTime = "";
  sunriseLocalTime = "";
  sunsetLocalTimeAfter30Minutes = "";
}

unsigned long timeCollectAPI = 0;

String RTC::getSunsetLocalTime() {
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  
  if (httpResponseCode > 0) {

      String payload = http.getString();

      DynamicJsonDocument doc(1024);  // Khởi tạo đối tượng JSON
      deserializeJson(doc, payload);
      const char* sunsetUTC = doc["results"]["sunset"];

      int hour, minute, second;
      sscanf(sunsetUTC + 11, "%d:%d:%d", &hour, &minute, &second);
      long sunsetTimeUTC = hour * 3600 + minute * 60 + second;

      long sunsetTimeLocal = sunsetTimeUTC + timezoneOffset;
      int localHour = (sunsetTimeLocal / 3600) % 24;
      int localMinute = (sunsetTimeLocal % 3600) / 60;
      int localSecond = sunsetTimeLocal % 60;

      sunsetLocalTime = String(localHour) + ":" + 
                        String(localMinute) + ":" + 
                        String(localSecond);
      timeCollectAPI = millis();
      return sunsetLocalTime;
  } else {
      return "Không thể lấy dữ liệu từ API";
  }
  
  http.end();
}

String RTC::getSunriseLocalTime() {
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  
  if (httpResponseCode > 0) {

      String payload = http.getString();
      

      DynamicJsonDocument doc(1024); 
      deserializeJson(doc, payload);
      const char* sunriseUTC = doc["results"]["sunrise"];

      int hour, minute, second;
      sscanf(sunriseUTC + 11, "%d:%d:%d", &hour, &minute, &second);
      long sunriseTimeUTC = hour * 3600 + minute * 60 + second;

      long sunriseTimeLocal = sunriseTimeUTC + timezoneOffset;
      int localHour = (sunriseTimeLocal / 3600) % 24;
      int localMinute = (sunriseTimeLocal % 3600) / 60;
      int localSecond = sunriseTimeLocal % 60;

      sunriseLocalTime = String(localHour) + ":" + 
                        String(localMinute) + ":" + 
                        String(localSecond);
      timeCollectAPI = millis();
      return sunriseLocalTime;
  } else {
      return "Không thể lấy dữ liệu từ API";
  }
  
  http.end();
}

String RTC::getSunsetLocalTimeAfter30Minutes() {
  int hour, minute, second;
  sscanf(sunsetLocalTime.c_str(), "%d:%d:%d", &hour, &minute, &second);
  long sunsetLocalTimeInSeconds = hour * 3600 + minute * 60 + second;

  long sunsetLocalTimePlus30 = sunsetLocalTimeInSeconds + 30 * 60;

  int newLocalHour = (sunsetLocalTimePlus30 / 3600) % 24;
  int newLocalMinute = (sunsetLocalTimePlus30 % 3600) / 60;
  int newLocalSecond = sunsetLocalTimePlus30 % 60;

  sunsetLocalTimeAfter30Minutes = String(newLocalHour) + ":" + 
                                    String(newLocalMinute) + ":" + 
                                    String(newLocalSecond);
  return sunsetLocalTimeAfter30Minutes;
}

String RTC::getCachedSunsetTime() {
    return sunsetLocalTime;
}

String RTC::getCachedSunsetTime30Minutes() {
    return sunsetLocalTimeAfter30Minutes;
}

String RTC::getCachedSunriseTime() {
    return sunriseLocalTime;
}



void RTC::checkStatusDS3231(){
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
  }  
}

String RTC::checkTimeCurrent(){
  DateTime now = rtc.now();
  // Tạo một chuỗi từ giờ, phút, giây
  String timeString = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  return timeString;
}

int RTC::checkHourCurrent(){
  DateTime now = rtc.now();
  return now.hour();
}

int RTC::checkMinuteCurrent(){
  DateTime now = rtc.now();
  return now.minute();
}

String RTC::checkDayOfWeek(){
  DateTime now = rtc.now();
  return daysOfTheWeekRTC[now.dayOfTheWeek()];
}

String RTC::checkDayCurrrent(){
  DateTime now = rtc.now();
  return String(now.day());
}

String RTC::checkMonthCurrent(){
  DateTime now = rtc.now();
  return String(now.month());
}

String RTC::checkYearCurrent(){
  DateTime now = rtc.now();
  return String(now.year());
}

unsigned long RTC::convertToSeconds(String time) {

  int firstColon = time.indexOf(':'); 
  int secondColon = time.indexOf(':', firstColon + 1);

  String hourString = time.substring(0, firstColon);
  String minuteString = time.substring(firstColon + 1, secondColon);
  String secondString = time.substring(secondColon + 1);

  int hour = hourString.toInt();
  int minute = minuteString.toInt();
  int second = secondString.toInt();

  return (hour * 3600) + (minute * 60) + second;
}

unsigned long RTC::getTimeCollectAPI(){
  return timeCollectAPI;
}