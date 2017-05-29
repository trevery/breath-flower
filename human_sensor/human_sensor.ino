/* code to read human move, then control delay open and
 * close.
 * Author: Can
 * Date Created: 28th May. 2017
 * Version: 1.0
 */
 
int sensorPin = 3;
int relayPin = 2;
int live_time = 10*1000;

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
  int val=digitalRead(sensorPin); 
  Serial.println(val);
  if (val == 1) { 
    relayClose();
    delay(live_time);
  }
  else if(val == 0){
    relayOpen();
  } 
  else {
    return;
  }
  delay(100);
}
