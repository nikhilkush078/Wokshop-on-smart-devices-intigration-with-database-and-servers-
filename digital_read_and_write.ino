void setup() {
  pinMode(4, INPUT_PULLUP); // Set pin 4 as an input for a button
  pinMode(2, OUTPUT);       // Set pin 2 as an output for an LED
}

void loop() {
  // Check if the button pin is pulled down to Ground (pressed)
  if (digitalRead(4) == LOW) {
    digitalWrite(2, HIGH); // Turn LED ON
  } else {
    digitalWrite(2, LOW);  // Turn LED OFF
  }
}