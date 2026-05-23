void setup() {
  pinMode(34, INPUT);  // Set pin 34 as an analog input sensor
  pinMode(2, OUTPUT);  // Set pin 2 as an output for an LED
}

void loop() {
  // Read the variable value from the sensor
  int sensorValue = analogRead(34); 

  // If the sensor reading is high (greater than halfway)
  if (sensorValue > 2000) {
    digitalWrite(2, HIGH); // Turn LED ON
  } else {
    digitalWrite(2, LOW);  // Turn LED OFF
  }
}