#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const byte leftSensor = A0;
const byte rightSensor = A1; 
int leftValue;
int rightValue;
boolean turningLeft = false;
boolean turningRight = false;
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1); // M1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2); // M2


boolean isBlack(int analog_value){
  return (analog_value > 850 && analog_value < 930) ? true : false;
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor->setSpeed(150);
  leftMotor->run(FORWARD);
  leftMotor->run(RELEASE);
  rightMotor->setSpeed(150);
  rightMotor->run(FORWARD);
  rightMotor->run(RELEASE);
}

void loop() {
    boolean left = isBlack(analogRead(leftSensor));
    boolean right = isBlack(analogRead(rightSensor));
    if (!left && !right){
       turningLeft = false;
       turningRight = false;
       leftMotor->setSpeed(150);
       leftMotor->run(FORWARD);
       rightMotor->setSpeed(150);
       rightMotor->run(FORWARD);
    }
    else if(left && !right){
       if(!turningLeft){
           leftMotor->setSpeed(255);
           leftMotor->run(BACKWARD); // breakkkkkkk
           rightMotor->setSpeed(255);
           rightMotor->run(BACKWARD);
           turningLeft = true;
       }else{
          rightMotor -> setSpeed(200);
          rightMotor -> run(FORWARD);
       }
       
    }
    else if(!left && right){
      if(!turningLeft){
           leftMotor->setSpeed(255);
           leftMotor->run(BACKWARD); // breakkkkkkk
           rightMotor->setSpeed(255);
           rightMotor->run(BACKWARD);
           turningRight = true;
       }else{
          leftMotor -> setSpeed(200);
          leftMotor -> run(FORWARD);
       }
    }
}
