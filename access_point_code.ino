#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Servo.h>

const char *ssid = "ESP8266_AP";
const char *password = "12345678";

WiFiServer server(80);
Servo servos[5];

void setup() {
  Serial.begin(115200);
  
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();

  servos[0].attach(D2);
  servos[1].attach(D3);
  servos[2].attach(D4);
  servos[3].attach(D5);
  servos[4].attach(D6);
}

void loop() {
  WiFiClient client = server.available(); 

  if (client) {
    Serial.println("Client connected");
    String line = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (line.length() > 0) {
            int sensorValues[5];
            int index = 0;
            for (int i = 0; i < line.length(); i++) {
              if (line[i] == ',') {
                sensorValues[index] = line.substring(0, i).toInt();
                line = line.substring(i + 1);
                index++;
                i = 0;
              }
            }
            sensorValues[index] = line.toInt();

              if(sensorValues[0] >= 145){
                servos[0].write(180);
              }
              else {
                servos[0].write(0);
              }

              if(sensorValues[1] >= 245){
                servos[1].write(180);
              }
              else {
                servos[1].write(0);
              }

              if(sensorValues[2] >= 230){
                servos[2].write(180);
              }
              else {
                servos[2].write(0);
              }

              if(sensorValues[3] >= 210){
                servos[3].write(180);
              }
              else {
                servos[3].write(0);
              }

              if(sensorValues[4] >= 210){
                servos[4].write(180);
              }
              else {
                servos[4].write(0);
              }
          }
          line = "";
        } else {
          line += c;
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
