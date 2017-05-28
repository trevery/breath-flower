/*
 * Author: Can
 * Use for: read command from master Arduino through i2c
 *          then, move as the command
 * command: 0=still, 1=close&open, 2=close, 3 = open
 */
#include <Wire.h>
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


// command from master through i2c
byte command = 0;
int closeAndOpenTime = 10;

void setup() {
  Serial.begin(9600);
  //slave name
  Wire.begin(18);
  Wire.onReceive(receiveCommand);
  // stepper move speed
  stepper1.setMaxSpeed(100.0);
  stepper1.setAcceleration(50.0);
  // this line motor range 0-150
  stepper1.moveTo(-150);
  

  // for debug
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void receiveCommand(){ 
  command = Wire.read();
  //Serial.println("runFlower:");
  //Serial.println(command);
}
void funUp(){
  fun.setSpeed(255);
  fun.run(FORWARD);  
}
void funDown(){
  fun.setSpeed(0);
}
void flowersCloseAndOpen(){
    funUp();
    // movements of the flowers
    // close and open
    //stepper1.moveTo(150);
    if (stepper1.distanceToGo() == 0){
      stepper1.moveTo(-stepper1.currentPosition());
    }
    //Serial.println("one movement");
    stepper1.run();
    //stepper1.moveTo(150);
    //stepper1.run();
    //stepper1.moveTo(0);
    //stepper1.run();  
}

void flowersClose(){
  funUp();
  //move to TOP;maybe moveTo(0), 
  stepper1.moveTo(150);
  stepper1.run();
}

void flowersOpen(){
  funUp();
  stepper1.moveTo(-150);
  stepper1.run();
}
void flowersDown(){
  funDown();
  // go home
  stepper1.moveTo(-150);
  stepper1.run();
}
void loop(){
  //Serial.println("loop: ");
  Serial.println(command);
  if (command == 0){
    funDown();
    flowersDown();
  }
  else if(command == 1){
    //digitalWrite(LED_BUILTIN, HIGH);
    // setting up fun
    flowersCloseAndOpen();  
  }    

  // close
  else if(command == 2){
    flowersClose();
  } 
  // open
  else if(command == 3){
    flowersOpen();
  }    
  //delay(1000);
}
