// OUTPUT Pin Number Declration
int ledPin1 = 13;
int ledPin2 = 12;
int ledPin3 = 11;
int ledPin4 = 10;
int ledPin5 = 9;

// INPUT Pin Number Declaration
int inPin = 8; // button input (digial)
int analogInPin = 0; // potentiometer input A0

// VALUES read from each INPUT Pins
int buttonIn = 0;
int analogIn = 0;

// Variables 
int mode = 0; 
int bouncePin = 9;
int previousBouncePin;
boolean bounceBack = false;

int randPin;
int previousRandPin;

unsigned long previousClickTime;
unsigned long previousBlinkTime;

boolean ledAllOn = true; // led flag for all leds
void turnAllOff(){
   digitalWrite(ledPin1, LOW);
   digitalWrite(ledPin2, LOW);
   digitalWrite(ledPin3, LOW);
   digitalWrite(ledPin4, LOW);
   digitalWrite(ledPin5, LOW);
   ledAllOn = false;
}
void turnAllOn(){
   digitalWrite(ledPin1, HIGH);
   digitalWrite(ledPin2, HIGH);
   digitalWrite(ledPin3, HIGH);
   digitalWrite(ledPin4, HIGH);
   digitalWrite(ledPin5, HIGH);
   ledAllOn = true;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  
  pinMode(inPin, INPUT);  
  
  Serial.begin(9600);    
}

void loop() {
  
  // 
  unsigned long currentTime = millis();
  const long clickInterval = 300; // 300ms force delay between clicks to prevent double-clicks
  buttonIn = digitalRead(inPin);
  if((buttonIn == HIGH) && (currentTime - previousClickTime >= clickInterval)){
    previousClickTime = currentTime;
    mode = (mode + 1) % 5; // increments modes between 0 ~ 4
    turnAllOff();  
  }
  
  // Reads the potentiometer value from analog input, then maps it to blinkInterval
  analogIn = analogRead(analogInPin);
  int blinkInterval = map(analogIn, 0, 1023, 100, 1000); // maps the original analog output to 100ms to 1000ms
  
  switch(mode){
    case 0: // All off
      turnAllOff();
      break;
    case 1: // All on
      turnAllOn();
      break;
    case 2: // All flashing Mode
      if (currentTime - previousBlinkTime >= blinkInterval) {
         previousBlinkTime = currentTime;
         // if the LED is off turn it on and vice-versa:
         if (!ledAllOn) {
            turnAllOn();
         } else {
            turnAllOff();    
         }
      }
      break;
    case 3: // Bouncing Mode
         if (currentTime - previousBlinkTime >= blinkInterval) {
            previousBlinkTime = currentTime;
            digitalWrite(bouncePin, HIGH);
            digitalWrite(previousBouncePin, LOW);
            
            previousBouncePin = bouncePin;
            if(!bounceBack){
               bouncePin++;
              if(bouncePin > 13){
                 bounceBack = !bounceBack;
                 bouncePin = 13;
              }
            }
            else{
              bouncePin--;
              if(bouncePin < 9){
                bounceBack = !bounceBack;
                bouncePin = 9;
              }  
            }        
         }
      break;
    case 4: // Random led blinking Mode
      randPin = random(9, 14);
      if (currentTime - previousBlinkTime >= blinkInterval) {
         // save the last time you blinked the LED
         previousBlinkTime = currentTime;
         digitalWrite(randPin, HIGH);
         digitalWrite(previousRandPin, LOW);
         
         previousRandPin = randPin;   
      }
      break;
    default:
      Serial.print("error");
      break;
  }
}
