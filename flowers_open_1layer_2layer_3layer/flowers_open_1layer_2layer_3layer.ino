/*
 * Author: Can
 * To: first layer open and close; after 1s,second layer
 *     open and close,then,after 1s, third layers open 
 *     and close. 
 *     after 2.6s, all the flowers close.
 */

//#include <Wire.h>
#include <AccelStepper.h>
#include <AFMotor.h>

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

const int timeFlowersOpenAndClose = 10;
const int halfTime = timeFlowersOpenAndClose/2.0;
int delay_seconds = 2;
int delay_time = delay_seconds * 1000 ;


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
  stepper1.moveTo(-150);
  stepper1.run();
}

unsigned long open_time, current_time, live_time;
void setup(){
  stepper1.setMaxSpeed(80.0);
  stepper1.setAcceleration(40.0);
  stepper1.moveTo(-150);
  delay(delay_time);
  open_time = millis();
}

void loop(){
  current_time = millis();
  live_time = current_time - open_time;
  for(int i=0;i<2;i++){
    flowersCloseAndOpen(); 
    //delay(10000); 
  }
  // after 2.6s, all the flowers stop.
  if (live_time> 26000){
    while(1){
      //flowersOpen();
      delay(1000000);
    }
  }
//  while(1){  
//  }
  
  
/*
  //while(millis < 10000){
  for(int i=0;i<20;i++){
    if (i==0){
      //home
      flowersOpen();
    }
    if (i==1){
      delay(delay_time);
      flowersCloseAndOpen;
    }
    if (i>1){
      flowersCloseAndOpen;
    }
  }     
  //}
  //flowersOpen(); 
*/
}



