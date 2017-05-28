#include <Wire.h>

byte command = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  command = 1;
  
  Serial.println("Flower should be running.");
  
  Wire.beginTransmission(16);
  Wire.write(command);
  Wire.endTransmission();
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);

  command = 0;
  
  Serial.println("Flower should be stopped!");
  
  Wire.beginTransmission(16);
  Wire.write(command);
  Wire.endTransmission();
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  command = 1;
  
  Serial.println("Flower should be running.");
  
  Wire.beginTransmission(9);
  Wire.write(command);
  Wire.endTransmission();
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);

  command = 0;
  
  Serial.println("Flower should be stopped!");
  
  Wire.beginTransmission(9);
  Wire.write(command);
  Wire.endTransmission();
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
