#include <ESP8266WiFi.h>  
#include <PubSubClient.h>

// --- Network Configuration ---
const char* ssid     = "Airtel_kaml_0228";
const char* password = "Passward@078078";

// --- Local MQTT Broker Configuration ---
// CHANGE THIS: Replace with your laptop's actual IP address from 'hostname -I'
const char* mqtt_broker = "192.168.1.17"; 
const int mqtt_port = 1883;
const char* mqtt_topic = "home/led"; 

WiFiClient espClient;
PubSubClient client(espClient);

// --- Wi-Fi Connection Management ---
void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());
}

// --- MQTT Broker Connection Management ---
void connectToMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting Local MQTT connection... ");
    
    // Generate a unique random Client ID for the session connection frame
    String clientId = "ESP8266Client-" + String(random(0, 1000));
    
    if (client.connect(clientId.c_str())) {
      Serial.println("CONNECTED to Laptop Broker!");
      
      // Send SUBSCRIBE packet to the broker for our target channel topic
      client.subscribe(mqtt_topic);
      Serial.print("Subscribed to topic: ");
      Serial.println(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

// --- Inbound Packet Callback Function ---
// This wakes up automatically when the laptop broker pushes data down the TCP pipe
void checkIncomingMessage(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic [");
  Serial.print(topic);
  Serial.print("]: ");
  
  // Extract the first raw character byte from the payload structure
  char command = (char)payload[0];
  Serial.println(command);
  
  // Handle Onboard LED logic (Active-LOW: LOW turns it ON, HIGH turns it OFF)
  if (command == '1') {
    digitalWrite(LED_BUILTIN, LOW);  // Turn ON
    Serial.println("Action: Turning Onboard LED ON");
  }
  if (command == '0') {
    digitalWrite(LED_BUILTIN, HIGH); // Turn OFF
    Serial.println("Action: Turning Onboard LED OFF");
  }
}

void setup() {
  Serial.begin(115200);
  
  // Set up the internal macro-mapped built-in LED hardware channel
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Keep it off initially

  connectToWiFi();
  
  // Bind your underlying network socket, host endpoint details, and callback worker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(checkIncomingMessage);
}

void loop() {
  // If the background TCP pipe drops out, trigger the connection state machine
  if (!client.connected()) {
    connectToMQTT();
  }
  
  // CRITICAL: Processes keep-alive PING frames and services incoming buffer queues
  client.loop();
}