//Button Part
//Button pin
const int buttonLeft = 21;     // the number of the pushbutton pin
const int buttonRight = 20;     // the number of the pushbutton pin
//Button State
int buttonLeftState = 0;         // variable for reading the pushbutton status
int buttonRightState = 0;

//Servo Part
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int angle = 0;
//int angleSpeed;

void setup() {
  Serial.begin(9600);
  // initialize button pin as an input:
  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);

  //servo setup
  myservo.attach(2); // attaches the servo on GIO2 to the servo object
  
}

void loop() {
  ButtonControl();

}


void ButtonControl(){
  // read the state of the pushbutton value:
  buttonLeftState = digitalRead(buttonLeft);
  buttonRightState = digitalRead(buttonRight);
 
  if (buttonLeftState == HIGH && angle < 180) {
    
    angle++;
    myservo.write(angle); 
    delay(15);
    //Serial.print("left 1"); 
    
    
  } 
 


  if (buttonRightState == HIGH && angle > 0) {
    angle--;
    myservo.write(angle); 
    delay(15);
    //Serial.print("Right 1"); 
    
    //myservo.write(angle); 
  } 



  }
