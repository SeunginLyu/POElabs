
#include <Servo.h>

const byte POT = A0;

const byte SERVO_SPEED = 25;  //minimum number of milliseconds per degree)
const byte THETA_MAX = 180;
const byte THETA_MIN = 0;
const byte THETA_INCREMENT = 1;

const byte PHI_INCREMENT = 5;
const byte PHI_MAX = 180;

boolean flag = 0;

byte curr_theta = 90;
byte curr_phi = 90;

int pot_value;
String result = "";


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


void loop() {
  static unsigned long servo_time;
  // check time since last servo position update
  if ((millis() - servo_time) >= SERVO_SPEED) {
    servo_time = millis(); // save time reference for next position update
    if (curr_theta >= THETA_MAX || curr_theta <= THETA_MIN) {
      flag = (flag + 1) % 2;
      servo_phi.write((curr_phi + PHI_INCREMENT) % PHI_MAX);
      curr_phi = (curr_phi + PHI_INCREMENT) % PHI_MAX;
    }
    servo_theta.write(curr_theta + (flag * (-2 * THETA_INCREMENT)) + THETA_INCREMENT);
    curr_theta = curr_theta + (flag * (-2 * THETA_INCREMENT)) + THETA_INCREMENT;
    pot_value = analogRead(POT);
    result = String(pot_value) + "," + String(curr_theta) + "," + String(curr_phi);
    Serial.println(result);
  }
}
