#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Point directly to your laptop's local IP and the Python server port (8000)
const char* localServerUrl = "http://192.168.1.15:8000/led-status.txt";

void setup() {
  pinMode(2, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(10);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(localServerUrl); // Polling your laptop instead of GitHub!

    if (http.GET() == 200) {
      String payload = http.getString();
      payload.trim(); 

      if (payload == "1") digitalWrite(2, HIGH);
      if (payload == "0") digitalWrite(2, LOW);
    }
    http.end(); 
  }
  delay(1000); 
}