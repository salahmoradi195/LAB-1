const int fanPin = 9;       // PWM pin to fan (through Darlington)
const int potPin = A0;      // Potentiometer pin
const int onDuration = 5000;    // Fan ON duration in ms (5 sec)
const int cycleDuration = 15000; // Total cycle duration in ms (15 sec)

unsigned long previousMillis = 0;

void setup() {
  pinMode(fanPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  int potValue = analogRead(potPin);            // Read potentiometer
  int pwmValue = map(potValue, 0, 1023, 0, 255); // Map to PWM

  // Determine if fan should be ON or OFF
  if ((currentMillis % cycleDuration) < onDuration) {
    analogWrite(fanPin, pwmValue); // PWM fan speed
  } else {
    analogWrite(fanPin, 0);        // Turn fan off
  }
}
