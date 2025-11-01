const int ledPin = 13;  // Built-in LED on Arduino Uno
const int buttonPin = 2; // INT0 is digital pin 2

volatile bool ledState = false; // Variable to track LED state
ISR(toggleLED) {
  ledState = !ledState;       // Toggle LED state
  digitalWrite(ledPin, ledState);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor
  
  // Attach external interrupt: INT0 (pin 2), falling edge trigger
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggleLED, FALLING);
}

void loop() {
  // Main loop does nothing; LED toggled in ISR
}


