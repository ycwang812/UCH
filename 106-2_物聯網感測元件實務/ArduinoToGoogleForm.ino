/* Sketch was generated by motoblockly 
 Website: http://www.motoblockly.com 
 Author: www.motoduino.com 
 Date: Tue Apr 03 2018 02:04:02 GMT+0800
 */ 
#include "motoWiFiEsp.h"

#include <SoftwareSerial.h>

#include <motoDHT.h>

// Your secret DevID from PushingBox.com.
char DEVID1[] = "v34D1138D151C5EB";
char serverName[] = "api.pushingbox.com";

String  temp;
String  hum;

SoftwareSerial esp8266_Serial(A5,A4);

WiFiEspClient esp_client;

int connect_status = WL_IDLE_STATUS;

String ipAddressToString(const IPAddress& ipAddress ) {
       return String(ipAddress[0]) + String(".")+
       String(ipAddress[1]) + String(".")+
       String(ipAddress[2]) + String(".")+
       String(ipAddress[3]);
}
DHT motoDHT(4, DHT11);

void setup()
{
  Serial.begin(9600);
  esp8266_Serial.begin(9600);

  pinMode(4, INPUT);
  motoDHT.begin();
    esp8266_Serial.listen();
  WiFi.init(&esp8266_Serial); 
  if(WiFi.status()==WL_NO_SHIELD) {
   Serial.println("Esp8266 module no present");
   while(true);
   }
  while(connect_status != WL_CONNECTED) {
   Serial.println("Connect to router...");
   connect_status = WiFi.begin("WiFi","0928583777");
  }
  Serial.println(ipAddressToString(WiFi.localIP()));

}


void loop()
{
    temp = motoDHT.readTemperature();
    hum = motoDHT.readHumidity();
    if (esp_client.connect("api.pushingbox.com",80) != 0) {
      esp_client.print("GET /pushingbox?devid=");
      esp_client.print(DEVID1);
      esp_client.print("&temp=");
      esp_client.print(String(temp));
      esp_client.print("&hum=");
      esp_client.print(String(hum));
      esp_client.println(" HTTP/1.1");
      esp_client.print("Host: ");
      esp_client.println(serverName);
      esp_client.println("User-Agent: Arduino");
      esp_client.println();
      esp_client.stop();
      Serial.println((String("溫度：") + String(temp) + String("℃") + String(", 濕度：") + String(hum) + String("%")));
      delay(5000);

    }

}
