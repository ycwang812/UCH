
/////////////////////////////////
//// 功能: WiFi ESP8266 Testing
//// 日期: June 2016 
//// 作者: Dennis
//////////////////////////

#include "motoWiFiEsp.h"

#include <SoftwareSerial.h>
SoftwareSerial esp8266_Serial(A5,A4);

WiFiEspClient esp_client;

int connect_status = WL_IDLE_STATUS;

String ipAddressToString(const IPAddress& ipAddress ) {
       return String(ipAddress[0]) + String(".")+
       String(ipAddress[1]) + String(".")+
       String(ipAddress[2]) + String(".")+
       String(ipAddress[3]);
}
void setup()
{
  Serial.begin(9600);
  esp8266_Serial.begin(9600);

    WiFi.init(&esp8266_Serial); 
  if(WiFi.status()==WL_NO_SHIELD) {
   Serial.println("Esp8266 module no present");
   while(true);
   }
  while(connect_status != WL_CONNECTED) {
   Serial.println("Connect to router...");
   connect_status = WiFi.begin("Motoduino","motoS4A123");
  }
  Serial.println((String("IP Address = ") + String(ipAddressToString(WiFi.localIP()))));

}


void loop()
{

}
