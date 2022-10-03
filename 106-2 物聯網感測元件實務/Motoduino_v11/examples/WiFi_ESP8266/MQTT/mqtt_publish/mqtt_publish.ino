#include "motoWiFiEsp.h"

#include <SoftwareSerial.h>
SoftwareSerial esp8266_Serial(A5,A4);

#include <motoMQTTClient.h>

WiFiEspClient esp_client;

int connect_status = WL_IDLE_STATUS;

MQTTClient mqtt_client;

String getTopicData(String myTopic, String inTopic, String payload) {
  if(inTopic == myTopic)
     return payload;
  else
     return "";
}
void messageReceived(String topic, String payload, char * bytes, unsigned int length)
{
  Serial.println(getTopicData("/iwot", topic, payload));
  Serial.println(getTopicData("/example", topic, payload));
}

void setup()
{
  Serial.begin(9600);
  esp8266_Serial.begin(9600);

  pinMode(A0, INPUT);
    WiFi.init(&esp8266_Serial); 
  if(WiFi.status()==WL_NO_SHIELD) {
   Serial.println("Esp8266 module no present");
   while(true);
   }
  while(connect_status != WL_CONNECTED) {
   Serial.println("Connect to router...");
   connect_status = WiFi.begin("YourSSID","SSIDPASSWORD");
  }
  mqtt_client.begin("mqtt broker", esp_client);
    while (!mqtt_client.connect("arduino")) {
      Serial.print(".");
      delay(1000);
    }

}


void loop()
{
    mqtt_client.loop();
    mqtt_client.publish("/iwot",String(analogRead(A0)));
    delay(5000);

}
