#include <WiFiNINA.h>
#define PubNub_BASE_CLIENT WiFiClient
#include <PubNub.h>
#include <ArduinoJson.h>
//#include <SparkFunLSM6DS3.h>
#include "Wire.h"

//**Details of your local Wifi Network
//Name of your access point
char ssid[] = "guan2";
//Wifi password
char pass[] = "jieguann";

int status = WL_IDLE_STATUS;       // the Wifi radio's status

// pubnub keys
char pubkey[] = "pub-c-20d4349a-3850-432b-a231-5bb68b08e867";
char subkey[] = "sub-c-e6324f72-3468-11eb-bb60-1afa7ba42f78";

// channel and ID data

const char* myID = "Jie"; // place your name here, this will be put into your "sender" value for an outgoing messsage

char publishChannel[] = "Data"; // channel to publish YOUR data
char readChannel[] = "Data"; // channel to read THEIR data

// JSON variables
StaticJsonDocument<200> dataToSend; // The JSON from the outgoing message
StaticJsonDocument<200> inMessage; // JSON object for receiving the incoming values
//create the names of the parameters you will use in your message
String JsonParamName1 = "publisher";
String JsonParamName2 = "distance";
int serverCheckRate = 50; //how often to publish/read data on PN
unsigned long lastCheck; //time of last publish
//These are the variables that will hold the values we will be using
const char* inMessagePublisher; 


//servo and distance sensor
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
int distanceRecive;



void setup() {
  
  Serial.begin(9600);

  //run this function to connect
  connectToPubNub();
  
  //servo setup
  myservo.attach(servoPin); 
  //distance sensor part
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  myservo.write(angle); 
}


void loop() 
{ 
  //update trigger value
 distanceValue();

//send and receive messages with PubNub, based on a timer
sendReceiveMessages(serverCheckRate);

///Do whatever you want with the data here!
servoTrigger();

   
}

void connectToPubNub()
{
    // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to the network, SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    Serial.print("*");

    // wait 2 seconds for connection:
    delay(2000);
  }

  // once you are connected :
  Serial.println();
  Serial.print("You're connected to ");
  Serial.println(ssid);
  
  PubNub.begin(pubkey, subkey);
  Serial.println("Connected to PubNub Server");

  
}

void sendReceiveMessages(int pollingRate)
{
    //connect, publish new messages, and check for incoming
    if((millis()-lastCheck)>=pollingRate)
    {
      //publish data
      sendMessage(publishChannel); // publish this value to PubNub

      //check for new incoming messages
      readMessage(readChannel);
      
      //save the time so timer works
      lastCheck=millis();
    }


  
}



void sendMessage(char channel[]) 
{

      Serial.print("Sending Message to ");
      Serial.print(channel);
      Serial.println(" Channel");
  
  char msg[64]; // variable for the JSON to be serialized into for your outgoing message
  
  // assemble the JSON to publish
  dataToSend[JsonParamName1] = myID; // first key value is publisher
  dataToSend[JsonParamName2] = distance; // second key value is the temperature

  serializeJson(dataToSend, msg); // serialize JSON to send - sending is the JSON object, and it is serializing it to the char msg
  Serial.println(msg);
  
  WiFiClient* client = PubNub.publish(channel, msg); // publish the variable char 
  if (!client) 
  {
    Serial.println("publishing error"); // if there is an error print it out 
  }
  else
  {
  Serial.print("   ***SUCCESS"); 
  }

}

void readMessage(char channel[]) 
{
  String msg;
    auto inputClient = PubNub.history(channel,1);
    if (!inputClient) 
    {
        Serial.println("message error");
        delay(1000);
        return;
    }
    HistoryCracker getMessage(inputClient);
    while (!getMessage.finished()) 
    {
        getMessage.get(msg);
        //basic error check to make sure the message has content
        if (msg.length() > 0) 
        {
          Serial.print("**Received Message on ");
          Serial.print(channel);
          Serial.println(" Channel");
          Serial.println(msg);
          //parse the incoming text into the JSON object

          deserializeJson(inMessage, msg); // parse the  JSON value received

           //read the values from the message and store them in local variables 
           inMessagePublisher = inMessage[JsonParamName1]; // this is will be "their name"
           distanceRecive = inMessage[JsonParamName2]; // the value of their Temperature sensor

           //calculate the average of the 2 temperatures
           

           
           Serial.println(distanceRecive);
           
           
        }
    }
    inputClient->stop();
  

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
//Serial.print("Distance: ");
//Serial.println(distance);
  }



  void servoTrigger(){
  if (distanceRecive > 20 && angle < 180 ) {
    
    angle = angle + 1;
    myservo.write(angle); 
    //delay(1);
  } 
 


  if (distanceRecive < 20 && angle > 0 ) {
    angle = angle - 1;
    myservo.write(angle); 
    //delay(1);
  
  } 
  }
