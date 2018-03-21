#include "motoWiFiEsp.h"

#include <SoftwareSerial.h>
SoftwareSerial esp8266_Serial(A5,A4);      
#include <motoMQTTClient.h>  //MQTT

int connect_status = WL_IDLE_STATUS;

WiFiEspClient esp_client;
MQTTClient client;   // MQTT

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
   connect_status = WiFi.begin("YOURSSID","PASSWORD");
  }
////////////// MQTT
    client.begin("mqtt broker", esp_client); 
  Serial.print("\nconnecting...");
  while (!client.connect("arduino")) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
  client.subscribe("/example");
  client.subscribe("/iot");
}


void loop() {
  client.loop();


}

String getTopicData(String mytopic, String topic, String payload)
{
    if(topic == mytopic)
       return payload;
    else
       return "";
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  String mypayload;
  
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
  mypayload = getTopicData("/iot", topic, payload);
  Serial.print("mypayload=");
  Serial.println(mypayload);
  
}



