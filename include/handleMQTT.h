#ifndef HANDLE_MQTT_H
#define HANDLE_MQTT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

class HandleMQTT {
  public:
    HandleMQTT();
    void connectAWS();
    void publishMessageSunriseSunsetLocalTime(String sunriseLocalTime, String sunsetLocalTime);
    void clientLoop();
    void publishMessageDay(String statusColor2);
    void publishMessageNight(String statusColor1, String statusColor2, String statusColor3);
  private:
    const char* AWSIoTPubTopic;
    const char* AWSIoTSubTopic;
    WiFiClientSecure net;
    PubSubClient client;
};

#endif
