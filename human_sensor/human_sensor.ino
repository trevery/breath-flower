/* code to read human move, then control delay open and
 * close.
 * Author: Can
 * Date Created: 28th May. 2017
 * Version: 1.0
 */
 
int sensorPin = 3;
int relayPin = 2;
long live_time = 50.0 * 1000;

void relayClose(){
  digitalWrite(relayPin,HIGH); 
} 

void relayOpen(){
  digitalWrite(relayPin, LOW);
}

void setup(){
  pinMode(sensorPin,INPUT); 
  pinMode(relayPin,OUTPUT); 
  Serial.begin(9600);
}
 
void loop(){
  boolean val=digitalRead(sensorPin); 
  Serial.println(val);
  if (val == 1) { 
    relayClose();
    delay(live_time);
    relayOpen();
  }
  else if(val == 0){
    relayOpen();
  } 
  delay(30000);
}
