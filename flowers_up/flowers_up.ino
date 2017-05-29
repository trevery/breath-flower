/*
 * Author: Can
 * To: first layer open and close; after 1s,second layer
 *     open and close,then,after 1s, third layers open 
 *     and close. 
 *     after 2.6s, all the flowers close.
 */

#include <SimpleTimer.h>
#include <AccelStepper.h>
#include <AFMotor.h>

//movement 1 timer
SimpleTimer timer1;

// setting up step1
AF_Stepper step1(200, 1);

void forwardstep1(){
  step1.onestep(FORWARD, SINGLE);
}
void backwardstep1(){
  step1.onestep(BACKWARD, SINGLE);
}

AccelStepper stepper1(forwardstep1, backwardstep1);

// setting up fun
AF_DCMotor fun(3);

const int timeFlowersOpenAndClose = 12.5;
const int halfTime = timeFlowersOpenAndClose/2.0;
int delay_seconds = 1;
int delay_time = delay_seconds * 1000 ;
//movement 1 needs 26s
long mov_1_interval = 26000;



void funUp(){
  fun.setSpeed(255);
}
void funDown(){
  fun.setSpeed(0);
}
void flowersCloseAndOpen(){
  funUp();
  //stepper1.moveTo(150);
  if(stepper1.distanceToGo() == 0){
    stepper1.moveTo(-stepper1.currentPosition());
  }
  stepper1.run();
}
void flowersOpen(){
  funUp();
  stepper1.moveTo(-150);
  stepper1.run();
}
void flowersClose(){
  funUp();
  stepper1.moveTo(150);
  stepper1.run();
}

void flowersDown(){
  funUp();
  stepper1.moveTo(-150);
  stepper1.run();
}
void flowersSleep(){
  delay(10000000);
}

void flowersHome(){
  funUp();
  stepper1.moveTo(0);
  stepper1.run();
}
void setup(){
  stepper1.setMaxSpeed(80.0);
  stepper1.setAcceleration(40.0);
  stepper1.moveTo(-150);
  delay(delay_time);
  timer1.setTimeout(mov_1_interval,flowersSleep);
}

void loop(){
  flowersCloseAndOpen();
  timer1.run();
}
