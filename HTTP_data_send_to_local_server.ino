#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "Airtel_kaml_0228";
const char* password = "Passward@078078";

// Keeping your local server endpoint layout
const char* server   = "http://192.168.1.17:5000/data"; 

void setup() {
  Serial.begin(115200);
  
  // Initialize Wi-Fi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client; // Required underlying TCP socket stream wrapper
    HTTPClient http;
    
    // Pass both the client stream wrapper and the endpoint destination URL
    if (http.begin(client, server)) {
      
      // Explicitly pull from the single analog reading pin 'A0' on ESP8266
      String data = "Value: " + String(analogRead(A0));
      
      // Specify the content type headers for a basic plain-text string upload
      http.addHeader("Content-Type", "text/plain");
      
      Serial.print("Sending POST payload: ");
      Serial.println(data);
      
      // Execute the POST request transaction
      int httpCode = http.POST(data);
      
      if (httpCode > 0) {
        Serial.printf("Server Response Code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
          String responseBody = http.getString();
          Serial.println("Server Response Text: " + responseBody);
        }
      } else {
        Serial.printf("POST Transaction Failed, Error: %s\n", http.errorToString(httpCode).c_str());
      }
      
      http.end(); // Deallocate connection objects cleanly from stack memory
    } else {
      Serial.println("Initialization failure contacting local server endpoint.");
    }
  }
  delay(2000); 
}