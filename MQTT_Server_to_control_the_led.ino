#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

// --- 1. THE CUSTOM STEPPING-STONE FUNCTIONS ---

// Function to handle local Wi-Fi connection
void connectToWiFi() {
  WiFi.begin("YOUR_WIFI_NAME", "YOUR_WIFI_PASSWORD");
  while (WiFi.status() != WL_CONNECTED) {
    delay(10);
  }
}

// Function to handle global Cloud MQTT connection
void connectToMQTT() {
  if (client.connect("ESP32_Fun_Client")) {
    client.subscribe("sanchit/workshop/led");
  }
}

// Function that handles what happens when an internet command arrives
void checkIncomingMessage(char* topic, byte* payload, unsigned int length) {
  char command = (char)payload[0];
  
  if (command == '1') digitalWrite(2, HIGH); // Internet sent 1 -> Turn ON
  if (command == '0') digitalWrite(2, LOW);  // Internet sent 0 -> Turn OFF
}


// --- 2. THE MAIN ARDUINO STRUCTURE ---

void setup() {
  pinMode(2, OUTPUT);

  connectToWiFi(); // Run our Wi-Fi function
  
  client.setServer("broker.hivemq.com", 1883);
  client.setCallback(checkIncomingMessage); // Link internet data to our function
}

void loop() {
  // If the cloud connection drops, try to reconnect using our function
  if (!client.connected()) {
    connectToMQTT();
    delay(1000);
  }

  client.loop(); // Keep the pipeline alive
}