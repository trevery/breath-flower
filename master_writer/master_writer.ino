#include <Wire.h>

char command = "";

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  command = "Y";
  
  Serial.println("Flower should be running.");
  
  Wire.beginTransmission(8);
  Wire.write(command);
  Wire.endTransmission();
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);

  command = "N";
  
  Serial.println("Flower should be stopped!");
  
  Wire.beginTransmission(8);
  Wire.write(command);
  Wire.endTransmission();
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(5000);
}
