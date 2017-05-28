#include <AccelStepper.h>
#include <AFMotor.h>

// setting motor1
AF_Stepper motor1(200,1);
AF_DCMotor fun(3);

void forwardstep1() {  
  motor1.onestep(FORWARD, SINGLE);
}
void backwardstep1() {  
  motor1.onestep(BACKWARD, SINGLE);
}

AccelStepper stepper1(forwardstep1, backwardstep1);

const int fanPin = A3;
byte command = 0;


void setup() {
  stepper1.setMaxSpeed(200.0);
  stepper1.setAcceleration(100.0);
  stepper1.moveTo(200);

  //pinMode(fanPin,OUTPUT);
  //fun.setSpeed(200);
  //fun.run(RELEASE);
  Serial.begin(9600);

}
 
void loop() {
  
  command = Serial.read();
  Serial.println(command);
  analogWrite(fanPin,255);
  if (stepper1.distanceToGo() == 0){
    fun.setSpeed(255);
    fun.run(FORWARD);
    stepper1.moveTo(-stepper1.currentPosition());
}
  stepper1.run();
}
