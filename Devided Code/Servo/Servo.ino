/* Sweep
  Servo by BARRAGAN <http://barraganstudio.com>
 http://arduino.cc/en/Tutorial/Sweep
*/
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int angle;
void setup() {
  myservo.attach(2); // attaches the servo on GIO2 to the servo object
  angle = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  for(angle = 0; angle < 180; angle ++)    // command to move from 0 degrees to 180 degrees 
  {                                  
    myservo.write(angle);                 //command to rotate the servo to the specified angle
    delay(15);                       
  } 
 
  delay(10);
  
  for(angle = 180; angle>=0; angle--)     // command to move from 180 degrees to 0 degrees 
  {                                
    myservo.write(angle);              //command to rotate the servo to the specified angle
    delay(5);                       
  } 

    delay(10);
}
