/****************************************************************************************************************************************************
 *  TITLE: 
 *  DESCRIPTION: 
 *
 *  By Frenoy Osburn
 *  YouTube Video: 
 *  BnBe Post: 
 ****************************************************************************************************************************************************/

#include <WiFiNINA.h> 
#include <PubSubClient.h>
#include "credentials.h"
const char* ssid = "guan2"; //Change it to your wifi name
const char* password = "jieguann"; //Change it to your wifi passwork
const char* mqttServer = "mqtt.eclipse.org";
const char* mqttUsername = "experiment5";
const char* mqttPassword = "12345678";

//char subTopic[] = "arduino/ledControl";     //payload[0] will control/set LED
char pubTopic[] = "ocadu/creationcomputation/jie";       //payload[0] will have ledState value
char subTopic[] = "ocadu/creationcomputation/jie";
WiFiClient wifiClient;
PubSubClient client(wifiClient);
long lastMsg = 0;
char msg[50];
int value = 0;


void setup_wifi() 
{
  delay(10);
  
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if 1 was received as first character
  if ((char)payload[0] == '1') 
  {
    //digitalWrite(LED_PIN, HIGH);   
    //ledState = 1;
    char payLoad[1];
    itoa(1, payLoad, 10);
    client.publish(pubTopic, payLoad);
  } 
  else 
  {
    //digitalWrite(LED_PIN, LOW); 
    //ledState = 0;
    char payLoad[1];
    itoa(0, payLoad, 10);
    client.publish(pubTopic, payLoad);
  }

}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ArduinoClient-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqttUsername, mqttPassword)) 
    {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe(subTopic);
    } else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() 
{
  //pinMode(LED_PIN, OUTPUT);     
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
}

void loop() 
{
  Mqtt();
}

void Mqtt(){
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) 
  {
    lastMsg = now;
    char payLoad[1];
    itoa(1, payLoad, 10);
    client.publish(pubTopic, payLoad);
  }
  }
