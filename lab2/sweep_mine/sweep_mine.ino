
#include <Servo.h>

const byte POT = A0;

const byte SERVO_SPEED = 50;  //minimum number of milliseconds per degree)
const byte THETA_MAX = 50;
const byte THETA_MIN = 0;
const byte THETA_INCREMENT = 1;

const byte PHI_INCREMENT = 1;
const byte PHI_MAX = 50;
const byte PHI_MIN = 0;


byte curr_theta = 50;
byte curr_phi = 50;


boolean flag = 0;
int pot_value;
String result = "";


Servo servo_theta;
Servo servo_phi;  // create servo object to control a servo
// twelve servo objects can be created on most boards
void setup() {
  servo_theta.attach(9); // attaches the servo on pin 9 to the servo object
  servo_phi.attach(10);  // attaches the servo on pin 10 to the servo object
  servo_theta.writeMicroseconds(700);
  servo_phi.writeMicroseconds(700);
  Serial.begin(9600);
}


void loop() {
  static unsigned long servo_time;
  // check time since last servo position update
  if ((millis() - servo_time) >= SERVO_SPEED) {
    servo_time = millis(); // save time reference for next position update
    if (curr_phi == PHI_MAX || curr_phi == PHI_MIN) {
      flag = (flag + 1) % 2;
      curr_theta = (curr_theta + THETA_INCREMENT) % THETA_MAX;
      servo_theta.write(curr_theta);
    }
    curr_phi = curr_phi + (flag * (-2 * PHI_INCREMENT)) + PHI_INCREMENT;
    servo_phi.write(curr_phi);
    pot_value = analogRead(POT);    
    result = String(pot_value) + "," + String(curr_theta) + "," + String(curr_phi);
    Serial.println(result);
  }
}
