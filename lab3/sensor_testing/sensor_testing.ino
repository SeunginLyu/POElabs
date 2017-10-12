#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const byte leftSensor = A0;
const byte rightSensor = A1; 
int leftValue;
int rightValue;
int left;
int right;
int leftSpeed;
int rightSpeed;
    
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1); // M1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2); // M2

boolean isBlack(int analog_value){
  return (analog_value > 880 && analog_value < 1000) ? true : false;
}

void setup() {
  Serial.begin(9600);    // set up Serial library at 9600 bps
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  Serial.println("Starting Lince Tracer.");
  Serial.println("To update break time, type breakTime,10. Default value is 5.");
  Serial.println("To update targetSpeed, type targetSpeed,100. Default valule is 30.");

  AFMS.begin();  // create with the default frequency 1.6KHz
  left = 20;
  right = 24;
  leftSpeed = left;
  rightSpeed = right;
  leftMotor->setSpeed(leftSpeed);
  leftMotor->run(FORWARD);
  leftMotor->run(RELEASE);
  rightMotor->setSpeed(rightSpeed);
  rightMotor->run(BACKWARD);
  rightMotor->run(RELEASE);
}

void loop() {
    if (Serial.available()){
       String cmd = Serial.readString();
       byte delimIndex = cmd.indexOf(',');
       String func = cmd.substring(0, delimIndex);
       String value = cmd.substring(delimIndex+1);
       if(func == "tracerSpeed"){
          leftSpeed = value.toInt();
          rightSpeed = value.toInt();
          Serial.println("Succesfully updated tracerSpeed to: " + value);
       }
       if(func == "left"){
        left = value.toInt();
        Serial.println("Succesfully updated leftSpeed to: " + value);
       }
       if(func == "right"){
        right = value.toInt();
        Serial.println("Succesfully updated rightSpeed to: " + value);
       }
       if(func == "reset"){
          leftSpeed = 20;
          rightSpeed = 24;
          Serial.println("Reset Complete");
       }
    }
    leftValue = analogRead(leftSensor);
    rightValue = analogRead(rightSensor);
    
    boolean leftBlack = isBlack(leftValue);
    boolean rightBlack = isBlack(rightValue);
    if (!leftBlack && !rightBlack){
       leftSpeed = left;
       rightSpeed = right;
       leftMotor->setSpeed(leftSpeed);
       rightMotor->setSpeed(rightSpeed);
       leftMotor->run(FORWARD);
       rightMotor->run(BACKWARD);
       Serial.println("straight");
    }
    else if(!leftBlack && rightBlack){ // turning right
      rightSpeed = 0;
      leftSpeed = left;
      leftMotor->setSpeed(leftSpeed);
      rightMotor->setSpeed(rightSpeed);
      leftMotor->run(FORWARD);
      rightMotor->run(RELEASE);
      Serial.println("turning right");
    }
    else if(leftBlack && !rightBlack){ // turning left
      leftSpeed = 0;
      rightSpeed = right;
      leftMotor->setSpeed(leftSpeed);
      rightMotor->setSpeed(rightSpeed);
      leftMotor->run(RELEASE);
      rightMotor->run(BACKWARD); 
       Serial.println("turning left");
    }
    Serial.print(leftValue);
    Serial.print(",");
    Serial.print(rightValue);
    Serial.print(",");
    Serial.print(leftSpeed);
    Serial.print(",");
    Serial.print(rightSpeed);
    Serial.println("");
}
