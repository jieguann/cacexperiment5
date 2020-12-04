//Servo Part
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int angle = 0;
const int servoPin = 2; // D2

//Button
//Button pin
const int button = 3; //D3     // the number of the pushbutton pin
//Button State
int buttonState = 0;      


void setup() {
  Serial.begin(9600); // Starts the serial communication
  
  //servo setup
  myservo.attach(servoPin); 
  //Button
  pinMode(button, INPUT);

  
}

void loop() {
  buttonState = digitalRead(button);
  servoTrigger();
}

void servoTrigger(){
  if (buttonState == HIGH && angle < 180) {
    
    angle++;
    myservo.write(angle); 
    delay(15);
  } 
 


  if (buttonState == LOW && angle > 0) {
    angle--;
    myservo.write(angle); 
    delay(15);
  
  } 
  }
