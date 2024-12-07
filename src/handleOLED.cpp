#include <handleOLED.h>
#include <rtc.h>

RTC rtc_oled;

HandleOLED::HandleOLED(int screenWidth, int screenHeight, int oledReset) : display(screenWidth, screenHeight, &Wire, oledReset), screenAddress(screenAddress) { 

}


void HandleOLED::init() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, screenAddress)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.display();
    delay(2000);
    display.clearDisplay();
}

void HandleOLED::displayTime() {
    display.setCursor(0, 15);
    display.setTextSize(2);

    int hour = rtc_oled.checkHourCurrent();
    int minute = rtc_oled.checkMinuteCurrent();

    if (hour < 10) {
        display.print("0"); // Add leading zero for single-digit minutes
    }
    display.print(minute);
    display.print(":");
    if (minute < 10) {
        display.print("0"); // Add leading zero for single-digit minutes
    }
    display.print(minute);
}

void HandleOLED::displayMoon() {
    display.drawBitmap(62, 10, moon, 24, 24, SSD1306_WHITE);
}

void HandleOLED::displaySunset() {
    display.drawBitmap(94, 0, sunset, 32, 32, SSD1306_WHITE);
}

void HandleOLED::displayNight() {
    display.drawBitmap(0, 0, night, 32, 32, SSD1306_WHITE);
}

void HandleOLED::displayGoodNight() {
    display.drawBitmap(0, 0, good_night, 32, 32, SSD1306_WHITE);
}

void HandleOLED::displayOLED(){
    display.display();
}

void HandleOLED::clearOLED(){
    display.clearDisplay();
}




