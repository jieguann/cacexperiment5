//Button Part
//Button pin
const int button = 3; //D3     // the number of the pushbutton pin
//Button State
int buttonState = 0;         // variable for reading the pushbutton status



void setup() {
  //Serial.begin(9600);
  // initialize button pin as an input:
  pinMode(button, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(button);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    delay(10);
    Serial.print("1"); 
  } else {
    // turn LED off:
    delay(10);
    Serial.print("0"); 
  }
}
