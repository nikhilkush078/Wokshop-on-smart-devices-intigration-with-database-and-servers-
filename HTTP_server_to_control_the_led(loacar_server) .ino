#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "Airtel_kaml_0228";
const char* password = "Passward@078078";

// Verified Local IP structure
const char* localServerUrl = "http://192.168.1.17:5000/led.txt"; 

void setup() {
  Serial.begin(115200);
  
  // Using LED_BUILTIN ensures the compiler selects the correct physical macro pin
  pinMode(LED_BUILTIN, OUTPUT); 
  
  // Explicitly force the LED off initially (Active-LOW means HIGH = OFF)
  digitalWrite(LED_BUILTIN, HIGH); 
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("ESP8266 IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, localServerUrl); 

    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      
      // CRITICAL: Clean hidden whitespace, linebreaks (\n), or carriage returns (\r)
      payload.trim(); 
      
      Serial.print("Server Payload: ");
      Serial.print("["); 
      Serial.print(payload);
      Serial.println("]"); // Brackets show you if hidden spaces still exist

      // Robust comparison using explicit character matching or string equivalence
      if (payload.indexOf('1') >= 0 || payload == "1") {
        digitalWrite(LED_BUILTIN, LOW);  // Active-LOW: ON
        Serial.println("Action: LED ON");
      } 
      else if (payload.indexOf('0') >= 0 || payload == "0") {
        digitalWrite(LED_BUILTIN, HIGH); // Active-LOW: OFF
        Serial.println("Action: LED OFF");
      }
      else {
        Serial.println("Warning: Received unrecognized payload string.");
      }
    } else {
      Serial.print("HTTP Error code: ");
      Serial.println(httpCode);
    }
    http.end(); 
  }
  delay(1000); 
}