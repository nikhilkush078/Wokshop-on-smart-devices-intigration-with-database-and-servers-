#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_Hotspot";
const char* password = "12345678";

WebServer server(80);
const int LED_PIN = 2; 

void setup() {
  pinMode(LED_PIN, OUTPUT);
  WiFi.softAP(ssid, password);

  // Inline logic instead of external functions
  server.on("/on", []() {
    digitalWrite(LED_PIN, HIGH);
    server.send(200, "text/plain", "ON");
  });

  server.on("/off", []() {
    digitalWrite(LED_PIN, LOW);
    server.send(200, "text/plain", "OFF");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}


// senond code for the same purpose but with different approach

#include <WiFi.h>

WiFiServer server(80);
const int LED_PIN = 2;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  WiFi.softAP("ESP32_Hotspot", "12345678");
  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Check if a phone is trying to connect
  
  if (client) {                           // If a phone connects
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle the LED (ON if OFF, OFF if ON)
    client.print("HTTP/1.1 200 OK\r\n\r\n toggled"); // Send a basic reply to the browser
    client.stop();                        // Disconnect the phone
  }
}



