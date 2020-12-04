//Button Part
//Button pin
const int buttonLeft = 21;     // the number of the pushbutton pin
const int buttonRight = 20;     // the number of the pushbutton pin
//Button State
int buttonLeftState = 0;         // variable for reading the pushbutton status
int buttonRightState = 0;


void setup() {
  
  //Serial.begin(9600);
  // initialize button pin as an input:
  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
}

void loop() {
  ButtonControl();
}


ButtonControl(){
  // read the state of the pushbutton value:
  buttonLeftState = digitalRead(buttonLeft);
  buttonRightState = digitalRead(buttonRight);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonLeftState == HIGH) {
    // turn LED on:
    delay(1000);
    Serial.print("left 1"); 
  } else {
    // turn LED off:
    delay(1000);
    Serial.print("left 0"); 
  }


  if (buttonRightState == HIGH) {
    // turn LED on:
    delay(1000);
    Serial.print("Right 1"); 
  } else {
    
    delay(1000);
    Serial.print("Right 0"); 
  }
  }
