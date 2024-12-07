#include "handleWifi.h"

WiFiMulti wifiMulti;

HandleWifi::HandleWifi(){
  
}

void HandleWifi::connectWifi(){
  // Kết nối WiFi
  wifiMulti.addAP("Trần Đại Vỉ", "hoilkhanga");
  wifiMulti.addAP("PTIT.HCM_SV", "");
  wifiMulti.addAP("PTIT.HCM_CanBo", "");
  wifiMulti.addAP("Thai Bao", "0869334749"); 
  wifiMulti.addAP("2D11", "vpkhoavtq92d11");
  wifiMulti.addAP("Bamos Coffee", "bamosxinchao");
  wifiMulti.addAP("CentralLibrary_user", "");
  wifiMulti.addAP("Work's Pied","yoursolution");
  wifiMulti.addAP("Y9 COFFEE", "y9xinchao");
  wifiMulti.addAP("NHA ANN", "camonquykhach");

  Serial.print("Connecting...");
  while (wifiMulti.run() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}