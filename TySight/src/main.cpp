#include <Arduino.h>
#include "poultrysonic.h"
#include "Temperature.h"
#include "vibrator.h"

// defines Poultrysonic pins
const int trigPin = 9;
const int echoPin = 10;

// defines temperature pins
const int dataPin = A0;
const int deadPin = A1;

// defines vibration pin
const int analogOutPin = 5;

// defines variables
long duration;
int distance;
int temperature;

void setup()
{
    // Set Poultrysonic pins
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input

    // Set Temperature pins
    pinMode(dataPin, INPUT);

    Serial.begin(9600);       // Starts the serial communication
}

void loop()
{
    // Create instance of Poultrysonic
    Poultrysonic ps (trigPin, echoPin);
    distance = ps.getDistance();

    // Create instance of temperature
    Temperature temp (dataPin, deadPin);
    temperature = temp.getTemperature();

    Vibrator vib (analogOutPin);
    vib.vibrate(distance);    

    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);

    // wait 2 ms to allow analog-to-digital converter to settle
    delay(2);
}