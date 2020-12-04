//Servo Part
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int angle = 90;
const int servoPin = 2; // D2

//Distance Sensor Part
const int trigPin = 21; //D21
const int echoPin = 20; //D20
// defines variables
long duration;
int distance;
int trigger;


void setup() {
  Serial.begin(9600); // Starts the serial communication
  
  //servo setup
  myservo.attach(servoPin); 
  //distance sensor part
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  myservo.write(angle); 
  
}

void loop() {
  distanceControl();
  distanceValue();
  servoTrigger();
}

void servoTrigger(){
  if (distance>20 && angle < 180) {
    
    angle++;
    myservo.write(angle); 
    delay(15);
  } 
 


  if (distance<20 && angle > 0) {
    angle--;
    myservo.write(angle); 
    delay(15);
  
  } 
  }

void distanceControl(){
  if (distance>20) {
    
    trigger = 1;
  } 
 


  if (distance<20) {
    trigger = 0;
  
  } 

  }


  void distanceValue(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
  }
