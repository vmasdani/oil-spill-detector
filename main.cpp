/*
    This is the main code of the oil spill detector and
    it is meant to be uploaded on a ESP-12E based 
    development board such as the WeMos or NodeMCU.

    This code reads the sensor data from the analog 
    pin of your ESP-12E development board and transmits
    it to your Firebase Realtime database.

    Pin diagram connection:
    -Analog output from multiplexer IC to pin AO
    -Pin D1 to select 0 of multiplexer IC
    -Pin D2 to select 1 of multiplexer IC
    -Pin D4 to select 2 of multiplexer IC
*/
// Uncomment the code below if you are using PlatformIO
// #include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>

// Set these to run example.
// your firebase project here
#define FIREBASE_HOST "example.firebaseio.com" 
// your firebase secret database key here
#define FIREBASE_AUTH "token_or_secret"
// your wifi SSID here
#define WIFI_SSID "SSID"
//your password here
#define WIFI_PASSWORD "PASSWORD"

void switchChannel(bool bit1, bool bit2, bool bit3);

// Declaration for the select pins to the multiplexer IC
int s0 = 5; // D1
int s1 = 4; // D2
int s2 = 2; // D4

void setup() {
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    Serial.begin(9600);
    // connect to wifi.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
    int reading1;
    int reading2;
    int condition;
    int thresholdValue;

    // switch channel to the sensor above the water 
    // input 0, s0 = 0, s1 = 0, s2 = 0
    switchChannel(false, false, false);
    reading1 = analogRead(0);
    delay(100);
    // switch channel to the sensor below the water
    // input 1, s0 = 1, s1 = 0, s2 = 0
    switchChannel(true, false, false);
    reading2 = analogRead(0);
    delay(100);

    // in my case, the threshold goes above 80
    // when oil is poured. You might want to do 
    // experiment yourself to get the desired value.

    thresholdValue = 80;

    if(reading2 - reading1 > thresholdValue){
        // set danger condition
        condition = 1;
    }
    else{
        // set safe condition
        condition = 0;
    }

    // set the value to Firebase Realtime Database
    Firebase.setInt("sensor/normalizedValue", reading1);
    Firebase.setInt("sensor/underwaterValue", reading2);
    Firebase.setInt("sensor/status", condition);
    
    // print into serial monitor in baudrate 9600
    Serial.print("Underwater: ");
    Serial.print(reading2);
    Serial.print("Above water: ");
    Serial.print(reading1);
    Serial.println(condition);
    delay(1000);
}

// function to switch the channel of the multiplexer IC
void switchChannel(bool bit1, bool bit2, bool bit3){
    digitalWrite(s0, bit1);
    digitalWrite(s1, bit2);
    digitalWrite(s2, bit3);
}
