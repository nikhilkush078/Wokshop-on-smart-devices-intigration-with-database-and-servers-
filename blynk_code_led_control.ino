#define BLYNK_TEMPLATE_ID "TMPL3olugJpeO"
#define BLYNK_TEMPLATE_NAME "ESP3E2"
#define BLYNK_AUTH_TOKEN    "87iZBMH9Gi4HHF74O66A0zR91Pxf8Bkk"

/* Comment this out to remove prints and save space */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Airtel_kaml_0228";
char pass[] = "Passward@078078";

// Define the physical LED pin. 
// GPIO 2 is standard for the onboard blue LED on most ESP32 boards.
const int ledPin = 2; 

BlynkTimer timer;

// This function is called every time the device connects to Blynk Cloud
BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncAll();
  Serial.println("Connected to Blynk Cloud!");
}

// This function runs every time the button state changes on the Blynk App
BLYNK_WRITE(V1) {
  // Read the incoming button value (0 or 1) from Virtual Pin V1
  int buttonState = param.asInt(); 
  
  // Write the value to the physical ESP32 pin
  digitalWrite(ledPin, buttonState);
  
  // Debug print to Serial Monitor
  Serial.print("Blynk Button Pressed! LED State: ");
  Serial.println(buttonState);
}

// Example of sending data to Blynk: Sends uptime every second
void myTimerEvent() {
  // Sending the uptime in seconds to Virtual Pin V2 so it doesn't conflict with the LED on V1
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup() {
  // Debug console
  Serial.begin(115200);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Setup Blynk connection
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}