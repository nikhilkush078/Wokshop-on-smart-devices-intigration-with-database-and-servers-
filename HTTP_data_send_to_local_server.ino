#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* server   = "http://192.168.1.15:8000/data"; 

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(10);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(server);
    
    String data = "Value: " + String(analogRead(34));
    http.POST(data);
    http.end(); 
  }
  delay(2000); 
}