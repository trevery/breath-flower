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

//movement 1 begin timer
SimpleTimer mov1_begin_timer;

//movement 1 live timer
SimpleTimer mov1_sleep_timer;

//movement 2 live timer
SimpleTimer timer2;

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

const int timeFlowersOpenAndClose = 12.5 * 1000;
const int halfTime = timeFlowersOpenAndClose/2.0;
//different layers ,different delay_time,
//1 layers: 0, 2 layers: 1, 3 layers: 2
int delay_seconds = 2;
int mov1_begin_time = delay_seconds * 1000 ;
long mov1_begin_delay = mov1_begin_time;

//movement 1 needs 26s
long mov1_live_time = 26000;

//long mov_2_interval = 0;


void funUp(){
  fun.setSpeed(255);
  fun.run(FORWARD);
}
void funDown(){
  fun.setSpeed(0);
  fun.run(FORWARD);
}
void flowersCloseAndOpen(){
  funUp();
  //stepper1.moveTo(150);
  if(stepper1.distanceToGo() == 0){
    stepper1.moveTo(-stepper1.currentPosition());
  }
  stepper1.run();
}
void flowers_close_and_open_with_times(int times){
  funUp();
  long live_time = times * timeFlowersOpenAndClose;
  boolean flag = 1;
  long previous_millis = millis();
  while(flag){
    long current_millis = millis();
    if(current_millis - previous_millis < live_time ){
      //previous_millis = current_millis;
      flowersCloseAndOpen();
      //mov1_sleep_timer.run();
    }
    else flag=0;
  }
  return; 
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

//keep open status and do nothing
void flowersSleep(int second){
  delay(second * 1000);
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
  
  delay(mov1_begin_time);
  // close and open 2 times
  flowers_close_and_open_with_times(2);
  //flowers sleep 200 s
  flowersSleep(200);
  // after 1 movement, sleep
  mov1_sleep_timer.setTimeout(mov1_live_time, flowersSleep);
  
}

void loop(){
  
}

