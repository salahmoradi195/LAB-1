void setup() {
  // put your setup code here, to run once:
  Serial.beging(9600);
  while(!serial);

}

void loop() {
  // put your main code here, to run repeatedly:
  int raw=analogRead(A1);
  float voltage=raw*(3.3/4095.0);

  Serial.print("analogvalue:");
  Serial.print(raw);
  Serial.print("-> voltage:");
  Serial.print(voltage);

}
