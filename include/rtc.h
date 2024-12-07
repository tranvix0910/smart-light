#ifndef RTC_H
#define RTC_H

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <RTClib.h>

class RTC {
    public:
        RTC();
        String getSunsetLocalTime();
        String getSunriseLocalTime();
        String getSunsetLocalTimeAfter30Minutes();
        void checkStatusDS3231();
        String checkTimeCurrent();
        int checkHourCurrent();
        int checkMinuteCurrent();
        String checkDayOfWeek();
        String checkDayCurrrent();
        String checkMonthCurrent();
        String checkYearCurrent();
        unsigned long convertToSeconds(String time);
        unsigned long getTimeCollectAPI();

        // Getter
        String getCachedSunsetTime();
        String getCachedSunsetTime30Minutes();
        String getCachedSunriseTime();
    private:
        
        String url;
        int timezoneOffset;
        
        String sunsetLocalTime;
        String sunsetLocalTimeAfter30Minutes;
        String sunriseLocalTime;
        
        RTC_DS3231 rtc;
};

#endif