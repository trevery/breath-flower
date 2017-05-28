/*
 * Authot: Can
 * Use for: master Arduino control slave Arduinos movement  
 * command: 0=still, 1=close&open, 2= close, 3=open
 */
#include <Wire.h>

byte command = 0;
int closeAndOpenTime = 1000;

void sendCommandToSlave(int slaveName, byte command){
    Wire.beginTransmission(slaveName);
    //Serial.println(command);
    Wire.write(command);
    Wire.endTransmission(); 
}

void flowersUp(){
  //section 1
  Serial.println("section 1");
  // 1 close and open
  sendCommandToSlave(1,1);
  delay(closeAndOpenTime);
  sendCommandToSlave(1,0);
  // 1-19 close and open
  for(int i = 1; i<20; i++){
    sendCommandToSlave(i,1);
  }
  delay(closeAndOpenTime);
  // delay 3000
  delay(3000);

  // section 2
  Serial.println("section 2");
  // 8,10,12,14,16,18 close and open
  for(int i=8; i<19; i+=2){
    sendCommandToSlave(i,1);
  }
  delay(closeAndOpenTime);
  for(int i=8; i<19; i+=2){
    sendCommandToSlave(i,0);
  }
  // 9,11,13,15,17,19 close and open
  for(int i=9; i< 20; i+=2){
    sendCommandToSlave(i,1);
  }
  delay(closeAndOpenTime);
  for(int i=9; i< 20; i+=2){
    sendCommandToSlave(i,0);
  }
  // 2-7 close and open
   for(int i=2; i<8; i++){
    sendCommandToSlave(i,1);
   }
  delay(closeAndOpenTime);
  for(int i=2; i<8; i++){
    sendCommandToSlave(i,0);
   }
  // 1 close and open
  sendCommandToSlave(1,1);
  delay(closeAndOpenTime);
  sendCommandToSlave(1,0);
  // delay 5000
  delay(5000);

  // section 3
  Serial.println("section 3");
  // 1 close
  sendCommandToSlave(1,2);
      // delay 450
  delay(450);
      // 2-7 close
  for(int i=2; i<8; i++){
    sendCommandToSlave(i,2);
  }
        // delay 450
   delay(450);     
        // 8-19 close
  for(int i=8; i<20; i++){
    sendCommandToSlave(i,2);
   }
   //1-19 open
   for(int i=1; i<20; i++){
    sendCommandToSlave(i,3);
   }
  // delay 3000
  delay(3000);
}

int peopleIsWatchingMe(){
  //if sensorUp(){}
  return 1;
  //else{
  //return 0;
  //}
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  flowersUp();
  command = 0;
}
