#include <Wire.h>
#include <AccelStepper.h>
#include <AFMotor.h>

AF_Stepper motor1(200, 1);

void forwardstep1(){
  motor1.onestep(FORWARD, SINGLE);
}
void backwardstep1(){
  motor1.onestep(BACKWARD, SINGLE);
}

AccelStepper stepper1(forwardstep1, backwardstep1);


char command = ' ';

void setup() {
  Wire.begin(8);
  Wire.onReceive(runFlower);
  stepper1.setMaxSpeed(200.0);
  stepper1.setAcceleration(100.0);
  stepper1.moveTo(150);

  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
}


void runFlower(){ 
  command = Wire.read();
  Serial.println(command);
}


void loop(){
  
  if (command == '#'){
  digitalWrite(LED_BUILTIN, HIGH);
  //Serial.println("Y");
    if (stepper1.distanceToGo() == 0)
  stepper1.moveTo(-stepper1.currentPosition());
    stepper1.run();
    
  }    
  else if (command == '?'){
    digitalWrite(LED_BUILTIN, LOW);
    //Serial.println("N");
    stepper1.moveTo(24);
    stepper1.run();
  }    
}
