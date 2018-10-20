#include <Arduino.h>
#include "poultrysonic.h"

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;

void setup()
{
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
    Serial.begin(9600);       // Starts the serial communication
}

void loop()
{
    // Updated version
    Poultrysonic ps (9, 10);
    distance = ps.getDistance;
   
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
}