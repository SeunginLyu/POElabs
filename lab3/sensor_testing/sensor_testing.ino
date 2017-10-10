#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const byte leftSensor = A0;
const byte rightSensor = A1; 
int leftValue;
int rightValue;
boolean turningLeft = false;
boolean turningRight = false;
int targetSpeed;
int breakTime;

    
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1); // M1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2); // M2

boolean isBlack(int analog_value){
  return (analog_value > 850 && analog_value < 930) ? true : false;
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Starting Lince Tracer.");
  Serial.println("To update break time, type breakTime,10. Default value is 10.");
  Serial.println("To update targetSpeed, type targetSpeed,100. Default valule is 150.");

  AFMS.begin();  // create with the default frequency 1.6KHz
  // Set the speed to start, from 0 (off) to 255 (max speed)
  targetSpeed = 150;
  breakTime = 50;
  leftMotor->setSpeed(targetSpeed);
  leftMotor->run(FORWARD);
  leftMotor->run(RELEASE);
  rightMotor->setSpeed(targetSpeed);
  rightMotor->run(FORWARD);
  rightMotor->run(RELEASE);
}

void loop() {
    if (Serial.available()){
       String cmd = Serial.readString();
       byte delimIndex = cmd.indexOf(',');
       String func = cmd.substring(0, delimIndex);
       String value = cmd.substring(delimIndex+1);
       if(func == "breakTime"){
          breakTime = value.toInt();
          Serial.println("Succesfully Updated breakTime to: " + value);
       }
       if(func == "targetSpeed"){
          targetSpeed = value.toInt();
          Serial.println("Succesfully targetSpeed to: " + value);
       }
    }
    boolean left = isBlack(analogRead(leftSensor));
    boolean right = isBlack(analogRead(rightSensor));
    if (!left && !right){
       turningLeft = false;
       turningRight = false;
       leftMotor->setSpeed(targetSpeed);
       leftMotor->run(FORWARD);
       rightMotor->setSpeed(targetSpeed);
       rightMotor->run(FORWARD);
    }
    else if(left && !right){
       if(!turningLeft){
           leftMotor->setSpeed(255);
           leftMotor->run(BACKWARD); // break
           rightMotor->setSpeed(255);
           rightMotor->run(BACKWARD);
           turningLeft = true;
           delay(breakTime);
       }else{
          rightMotor -> setSpeed(targetSpeed);
          rightMotor -> run(FORWARD);
       }
       
    }
    else if(!left && right){
      if(!turningLeft){
           leftMotor->setSpeed(255);
           leftMotor->run(BACKWARD); // break
           rightMotor->setSpeed(255);
           rightMotor->run(BACKWARD);
           turningRight = true;
           delay(breakTime);
       }else{
          leftMotor -> setSpeed(targetSpeed);
          leftMotor -> run(FORWARD);
       }
    }
}
