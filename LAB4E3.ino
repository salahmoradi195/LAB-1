const int fanPin = 9;   // PWM pin connected to MOSFET gate or BJT base through resistor
const int potPin = A0;  // Analog pin connected to trimmer

void setup() {
  pinMode(fanPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);        // Read potentiometer (0-1023)
  int pwmValue = map(potValue, 0, 1023, 0, 255); // Map to PWM (0-255)

  analogWrite(fanPin, pwmValue);            // Set fan speed
}
