#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* gistUrl  = "http://gist.githubusercontent.com/YOUR_USERNAME/YOUR_GIST_ID/raw/led.txt";

void setup() {
  pinMode(2, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(10);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(gistUrl); 

    if (http.GET() == 200) {
      String payload = http.getString();
      payload.trim(); // Keeps matching reliable by removing hidden spaces

      if (payload == "1") digitalWrite(2, HIGH);
      if (payload == "0") digitalWrite(2, LOW);
    }
    http.end(); 
  }
  delay(1000); 
}

// WE CAN USE THE GIST.GITUB.COM TO CONTROL THE LED BY SIMPLY EDITING THE CONTENT OF THE FILE "led.txt" TO "1" OR "0". WHEN THE CONTENT IS "1", THE LED WILL TURN ON, AND WHEN IT IS "0", THE LED WILL TURN OFF. MAKE SURE TO REPLACE "YOUR_WIFI_NAME", "YOUR_WIFI_PASSWORD", "YOUR_USERNAME", AND "YOUR_GIST_ID" WITH YOUR ACTUAL WIFI CREDENTIALS AND GIST DETAILS.
// OR WE CAN USE OR OWN LAPTOP AS A SERVER TO CONTROL THE LED BY SIMPLY CREATING A FILE "led.txt" IN THE SAME DIRECTORY AS THE CODE AND EDITING ITS CONTENT TO "1" OR "0". THEN WE CAN ACCESS THIS FILE USING THE LOCAL IP ADDRESS OF OUR LAPTOP AND THE PORT NUMBER WE CHOOSE TO SERVE THE FILE. FOR EXAMPLE, IF OUR LAPTOP'S IP ADDRESS IS
// FOR THAT WE NEED "http://192.168.1.15:8000/led-status.txt"; AND PYTHON SERVER TO SERVE THE FILE BY RUNNING "python -m http.server 8000" IN THE TERMINAL. THEN WE CAN CONTROL THE LED BY EDITING THE CONTENT OF "led-status.txt" TO "1" OR "0". WHEN THE CONTENT IS "1", THE LED WILL TURN ON, AND WHEN IT IS "0", THE LED WILL TURN OFF.
