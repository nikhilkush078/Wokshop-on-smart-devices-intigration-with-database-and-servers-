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
  if (!client) return; 

  // Read what the browser typed in the address bar
  String req = client.readStringUntil('\r');

  // Direct action checks
  if (req.indexOf("/on")  != -1) digitalWrite(2, HIGH);
  if (req.indexOf("/off") != -1) digitalWrite(2, LOW);

  // 1. Send standard web success headers
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close\r\n"); 

  // 2. Serve the bare-minimum webpage directly from the ESP32 memory
  client.println("<!DOCTYPE html><html><body>");
  client.println("<h1>ESP32 Controller</h1>");
  
  // Script targets window.location.origin so it automatically uses the ESP32's own IP address!
  client.println("<button onclick=\"fetch(window.location.origin+'/on',{mode:'no-cors'})\">ON</button>");
  client.println("<button onclick=\"fetch(window.location.origin+'/off',{mode:'no-cors'})\">OFF</button>");
  
  client.println("</body></html>");

  // Disconnect to complete the page render
  client.stop();
}