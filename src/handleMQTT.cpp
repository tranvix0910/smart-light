#include "handleMQTT.h"
#include "secrets.h"    
#include "rtc.h"

HandleMQTT::HandleMQTT() : client(net){
    net = WiFiClientSecure();
    AWSIoTPubTopic = "esp32/pub";
    // AWSIoTSubTopic = "esp32/sub";
}

void HandleMQTT::publishMessageSunriseSunsetLocalTime(String sunriseLocalTime, String sunsetLocalTime) {
  StaticJsonDocument<200> doc;
  doc["sunriseTime"] = sunriseLocalTime;
  doc["sunsetTime"] = sunsetLocalTime;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
  client.publish(AWSIoTPubTopic, jsonBuffer);
}

void HandleMQTT::publishMessageDay(String statusColor2) {
  StaticJsonDocument<200> doc;
  doc["isDay"] = true;
  doc["statusColor2"] = statusColor2;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  client.publish(AWSIoTPubTopic, jsonBuffer);
}

void HandleMQTT::publishMessageNight(String statusColor1, String statusColor2, String statusColor3) {
  StaticJsonDocument<200> doc;
  doc["isDay"] = false;
  doc["statusColor"]["statusColor1"] = statusColor1;
  doc["statusColor"]["statusColor2"] = statusColor2;
  doc["statusColor"]["statusColor3"] = statusColor3;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  client.publish(AWSIoTPubTopic, jsonBuffer);
}
 
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}

void HandleMQTT::connectAWS(){
// Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // // Subscribe to a topic
  // client.subscribe(AWSIoTSubTopic);
 
  Serial.println("AWS IoT Connected!");
}

void HandleMQTT::clientLoop() {
  client.loop(); // Gọi hàm loop của PubSubClient
}
