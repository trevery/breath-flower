/*
 * Author: Can
 * To: first layer open and close; after 1s,second layer
 *     open and close,then,after 1s, third layers open 
 *     and close. 
 *     after 2.6s, all the flowers close.
 */

//#include <SimpleTimer.h>
#include <AccelStepper.h>
#include <AFMotor.h>

//movement 1 begin timer
//SimpleTimer mov1_begin_timer;

//movement 1 live timer
//SimpleTimer mov1_sleep_timer;

//movement 2 live timer
//SimpleTimer timer2;

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

const long timeFlowersOpenAndClose = 11.2 * 1000;
const long halfTime = timeFlowersOpenAndClose/2.0;
//different layers ,different delay_time,
//1 layers: 0, 2 layers: 1, 3 layers: 2
//int delay_seconds = 2;

/*
 * CONFIG:
 */
 
// isHome
boolean mov1_isHome = 0;
boolean mov2_isHome = 0;
// begin_delay_seconds

int mov1_delay_seconds = 2;
int mov2_delay_seconds = 0;

/*
 * CONFIG
 */

long mov1_begin_time = mov1_delay_seconds * 1000 ;
long mov2_begin_time = mov2_delay_seconds * 1000 ;
 

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
  stepper1.moveTo(-200);
  stepper1.run();
}
void flowers_home(){
  funUp();
  long home_time = 0;
  long previous_time = millis();
  int flag = 1;
  while(flag){
    long current_time = millis();
    if(current_time - previous_time < home_time){
      flowersHome();
    }
    else{
      flag = 0;
    }
  }
}
void setup(){
  stepper1.setMaxSpeed(80.0);
  stepper1.setAcceleration(40.0);
  //stepper1.moveTo(-150);
//      stepper1.run();
  long previous_millis = millis();
  boolean flag = 1;
  long jerk_time = halfTime;
  while(flag){
    long current_millis = millis();
    if(current_millis - previous_millis < jerk_time ){
      stepper1.moveTo(-150);
      stepper1.run();
    }
    else flag =0;
  }
// movement 1 
  // begin at 2 second.
  delay(mov1_begin_time);
  flowers_close_and_open_with_times(2);
// movements 2
  if(mov2_isHome == 1){
    flowers_home();
  }
  else{
    delay(mov2_begin_time);
    flowers_close_and_open_with_times(1);
  }
  
  
// 
//  //movements 4
//  if(mov4_isHome = 1){
//    flowersHome();
//  }
//  else{
//    delay(mov4_begin_time);
//    flowers_close_and_open_with_times(1);
//  }
}

void loop(){
  
}

