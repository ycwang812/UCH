
/////////////////////////////////
//// 功能: WiFi手機無線遙控車 (ESP8266)    Station Mode
//// 日期: June 2016 
//// 作者: Dennis
//////////////////////////

#include "motoWiFiEsp.h"

#include <SoftwareSerial.h>
SoftwareSerial esp8266_Serial(3,2);

#include <Wire.h>
#include <motoLiquidCrystal_I2C.h>

String  data;
WiFiEspClient esp_client;

int connect_status = WL_IDLE_STATUS;

WiFiEspServer esp_server(80);

LiquidCrystal_I2C mylcd(0x27,16,2);

String ipAddressToString(const IPAddress& ipAddress ) {
       return String(ipAddress[0]) + String(".")+
       String(ipAddress[1]) + String(".")+
       String(ipAddress[2]) + String(".")+
       String(ipAddress[3]);
}
int checkServerDataAvailable( ) {
       esp_client = esp_server.available();
       return esp_client;
}
String clientDataReceive( ) {
  uint8_t myData[256]={0};
 int i=0;
 while(1) {
    if (esp_client.available()) {
        char c = esp_client.read();
        myData[i++] = c;
    }else{
       String inData((const char*)myData);
       return inData;
    }
  }
  return "";
}
void forward() {
  digitalWrite(10,HIGH);
  analogWrite(5,250);
  digitalWrite(11,HIGH);
  analogWrite(6,250);
}

void left() {
  digitalWrite(10,HIGH);
  analogWrite(5,250);
  digitalWrite(11,LOW);
  analogWrite(6,0);
}

void backward() {
  digitalWrite(10,LOW);
  analogWrite(5,250);
  digitalWrite(11,LOW);
  analogWrite(6,250);
}

void right() {
  digitalWrite(10,LOW);
  analogWrite(5,0);
  digitalWrite(11,HIGH);
  analogWrite(6,250);
}

void stop() {
  analogWrite(5,0);
  analogWrite(6,0);
}

void setup()
{
  Serial.begin(9600);
  esp8266_Serial.begin(9600);

  mylcd.init();

  mylcd.backlight();

    data = "";
  WiFi.init(&esp8266_Serial); 
  if(WiFi.status()==WL_NO_SHIELD) {
   Serial.println("Esp8266 module no present");
   while(true);
   }
  while(connect_status != WL_CONNECTED) {
   Serial.println("Connect to router...");
   connect_status = WiFi.begin("Motoduino","123456789");
  }
  esp_server.begin();
  mylcd.print(ipAddressToString(WiFi.localIP()));

  pinMode(10, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
}


void loop()
{
    if (checkServerDataAvailable() != 0) {
      data = clientDataReceive();
      Serial.println(data);
      if (data.charAt(0) == 'f') {
        forward();

      } else if (data.charAt(0) == 'b') {
        backward();
      } else if (data.charAt(0) == 'l') {
        left();
      } else if (data.charAt(0) == 'r') {
        right();
      } else if (data.charAt(0) == 's') {
        stop();
      }

    }

}