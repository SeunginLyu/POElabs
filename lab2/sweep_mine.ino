
#include <Servo.h>

const int SERVO_SPEED = 25;  //minimum number of milliseconds per degree)

const int THETA_MAX = 180;    // variable to store the servo position
const int THETA_MIN = 0;
const int THETA_INCREMENT = 1;

const int PHI_INCREMENT = 5;
const int PHI_MAX = 180;

boolean flag = 0;
int curr_theta = 90;
int curr_phi = 90;

Servo servo_theta;
Servo servo_phi;  // create servo object to control a servo
// twelve servo objects can be created on most boards
void setup() {
  servo_theta.attach(9); // attaches the servo on pin 9 to the servo object
  servo_phi.attach(10);  // attaches the servo on pin 10 to the servo object
  servo_theta.writeMicroseconds(1500);
  servo_phi.writeMicroseconds(1500);
  Serial.begin(9600);
}

// don't use servo.read

void loop(){
 static unsigned long servo_time;

 // check time since last servo position update 
 if ((millis()-servo_time) >= SERVO_SPEED) {
//   curr_theta = servo_theta.read();
  
   servo_time = millis(); // save time reference for next position update
   if(curr_theta >= THETA_MAX || curr_theta <= THETA_MIN){
    flag = (flag + 1) % 2;
//    curr_phi = servo_phi.read();
    servo_phi.write((curr_phi + PHI_INCREMENT) % PHI_MAX);;
   }
   servo_theta.write(curr_theta + (flag*(-2*THETA_INCREMENT)) + THETA_INCREMENT);   
 }
}
