#include <ESP8266WiFi.h>
#include <Wire.h>

const char *ssid = "ESP8266_AP";
const char *password = "12345678";

const char *host = "192.168.4.1";  

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);


  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

int readFlexSensor(int channel) {
  Wire.beginTransmission(0x48);
  Wire.write(0x40 + channel); 
  Wire.endTransmission();
  Wire.requestFrom(0x48, 1);
  int value = Wire.read();
  return value;
}

void loop() {
  WiFiClient client;

  if (!client.connect(host, 80)) {
    Serial.println("Connection to host failed");
    delay(1000);
    return;
  }

  String sensorData1 = "";
  for (int i = 0; i < 4; i++) {
    int sensorValue = readFlexSensor(i);
    sensorData1 += String(sensorValue) + ",";
  }
  int sensorValue = analogRead(A0);
  String sensorData = sensorData1 + String(sensorValue) ;


  sensorData = sensorData.substring(0, sensorData.length() - 1); 

  client.println(sensorData);
  Serial.println("Sent: " + sensorData);

  client.stop();
  delay(1000);
}
