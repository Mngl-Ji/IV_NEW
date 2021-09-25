
#include <WiFi.h>
#include "ThingSpeak.h"
const char* ssid =  "Redmi";     // enter your wifi name
const char* password =  "1234567a";      // enter your wifi password
WiFiClient  client;

unsigned long myChannelNumber = 6;
const char * myWriteAPIKey = "55CD8TN8QTN5DELH";  

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

const int Analog_channel_pin1= 34;
const int Analog_channel_pin2= 35;

int LED2 = 5;
int LED3 = 18;
int LED1 = 19; 
int ADC_VALUE1 = 0;
int ADC_VALUE2 = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  Serial.begin(115200);  //Initialize serial
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }
    // Get a new Voltage reading
    ADC_VALUE1 = analogRead(Analog_channel_pin1);
    float voltage1= (ADC_VALUE1 * 5 ) / (4095);
    ADC_VALUE2 = analogRead(Analog_channel_pin2);
    float voltage2= (ADC_VALUE2 * 5 ) / (4095);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    Serial.print("Voltage1 = ");
    Serial.print(voltage1);
    Serial.println("volts");
    Serial.print("Voltage2 = ");
    Serial.print(voltage2);
    Serial.println("volt");
    // set the fields with the values
    ThingSpeak.setField(1, voltage1);
    //ThingSpeak.setField(1, VoltageF);
    ThingSpeak.setField(2, voltage2);
    delay(5000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    delay(2000);

    
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    float voltage12=voltage1;
    float voltage22=voltage2;
    Serial.print("Voltage12 = ");
    Serial.print(voltage12);
    Serial.println("volts");
    Serial.print("Voltage22 = ");
    Serial.print(voltage12);
    Serial.println("volt");
    // set the fields with the values
    ThingSpeak.setField(3, voltage12);
    //ThingSpeak.setField(1, VoltageF);
    ThingSpeak.setField(4, voltage22);
    delay(5000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    delay(2000);

    
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    float voltage13=voltage1;
    float voltage23=voltage2;
    Serial.print("Voltage13 = ");
    Serial.print(voltage13);
    Serial.println("volts");
    Serial.print("Voltage23 = ");
    Serial.print(voltage13);
    Serial.println("volt");
    // set the fields with the values
    ThingSpeak.setField(5, voltage13);
    //ThingSpeak.setField(1, VoltageF);
    ThingSpeak.setField(6, voltage23);
    delay(5000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    delay(2000);
    

     
    /*digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    delay(5000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    delay(5000);
   

    // set the fields with the values
    ThingSpeak.setField(1, voltage1);
    //ThingSpeak.setField(1, VoltageF);
    ThingSpeak.setField(2, voltage2);
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1. */



    
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
  
}
