void setup() {
  pinMode(2, OUTPUT); // Set pin 2 as an output for an LED
}

void loop() {
  digitalWrite(2, HIGH); // Turn the LED ON
  delay(1000);           // Wait for 1 second
  
  digitalWrite(2, LOW);  // Turn the LED OFF
  delay(1000);           // Wait for 1 second
}