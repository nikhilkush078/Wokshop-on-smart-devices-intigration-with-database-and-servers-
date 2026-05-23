void setup() {
  // Pin 34 will read the raw analog input sensor
  pinMode(34, INPUT);
}

void loop() {
  // 1. Read the raw analog voltage from the sensor (gives a number from 0 to 4095)
  int rawValue = analogRead(34);

  // 2. Scale the number down from the 0-4095 range to the 0-255 PWM range
  int pwmValue = map(rawValue, 0, 4095, 0, 255);

  // 3. Output that scaled value directly as a PWM signal on Pin 9
  analogWrite(9, pwmValue);

  // A tiny pause to keep the processor stable
  delay(10);
}