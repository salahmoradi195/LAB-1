#include <PinChangeInterrupt.h>
volatile bool myled=false;
void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  pinMode(8,INPUT_PULLUP);
  attachPCINT(digitalPinToPCINT(8),toggle,FALLING);

}

void loop() {
  // put your main code here, to run repeatedly:

}
 void toggle()
 {
  myled=!myled;
  digitalWrite(13,myled);
 }
