#include <WiFi.h>

WiFiServer server(80);

void setup() {
  pinMode(2, OUTPUT);

  // Connect to your Wi-Fi network instantly
  WiFi.begin("YOUR_WIFI_NAME", "YOUR_WIFI_PASSWORD");
  while (WiFi.status() != WL_CONNECTED) delay(10);

  server.begin();
}

void loop() {
  // Directly grab any incoming browser connection
  WiFiClient client = server.available();
  if (!client) return; // Skip everything else if no one is connecting

  // Read what the browser typed in the address bar
  String req = client.readStringUntil('\r');

  // Direct action checks
  if (req.indexOf("/on")  != -1) digitalWrite(2, HIGH);
  if (req.indexOf("/off") != -1) digitalWrite(2, LOW);

  // Send a minimal reply and immediately disconnect
  client.print("Done!");
  client.stop();
}