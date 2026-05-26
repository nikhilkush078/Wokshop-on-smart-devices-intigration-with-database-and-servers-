#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid     = "Airtel_kaml_0228";
const char* password = "Passward@078078";

// UPDATED: Pointing to your new raw Gist link
const char* gistUrl = "https://pastebin.com/raw/xbmLvZcg"; 

WiFiClientSecure secureClient;

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, HIGH); // Turn off initially (Active-LOW)
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  
  secureClient.setInsecure(); // Bypass SSL certificate verification
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    Serial.println("Polling your new GitHub Gist...");
    
    if (http.begin(secureClient, gistUrl)) {
      int httpCode = http.GET();
      
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        payload.trim(); 
        
        Serial.print("Gist Payload: [");
        Serial.print(payload);
        Serial.println("]");

        // Hardware Logic Parsing
        if (payload.indexOf('1') >= 0 || payload == "1") {
          digitalWrite(LED_BUILTIN, LOW);  // Onboard LED ON
          Serial.println("Action: LED ON");
        } 
        else if (payload.indexOf('0') >= 0 || payload == "0") {
          digitalWrite(LED_BUILTIN, HIGH); // Onboard LED OFF
          Serial.println("Action: LED OFF");
        }
      } else {
        Serial.print("HTTP Secure Error code: ");
        Serial.println(httpCode); 
      }
      http.end(); 
    } else {
      Serial.println("Unable to connect to the secure host endpoint.");
    }
  }
  delay(5000); 
}