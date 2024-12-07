#include "ledControl.h"

LedControl::LedControl() : red(17), green(16), blue(4){

}

void LedControl::almostDawn(){
  Serial.println("Trời vừa tối!");
  analogWrite(red, 255);
  analogWrite(green, 165);
  analogWrite(blue, 0);
}

void LedControl::almostDawnAfter30Minutes(){
  Serial.println("Mặt trời đã lặn được 30'!");
  analogWrite(red, 255);
  analogWrite(green, 255);
  analogWrite(blue, 200);
}

void LedControl::beforeTimeForSleep(){
  Serial.println("Hãy chuẩn bị đi ngủ!");
  analogWrite(red, 255);
  analogWrite(green, 100);
  analogWrite(blue, 0);
}

void LedControl::turnOffAllLed(){
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 0);
}

int LedControl::getRed() {
    return red;
}

int LedControl::getBlue() {
    return green; 
}

int LedControl::getGreen() {
    return blue; 
}