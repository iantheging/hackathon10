#include <Arduino.h>

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;
int count = 0;
int distanceArr[10];

int getDistance(int trigPin, int echoPin)
{

    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = duration * 0.034 / 2;

    return distance;
}

int errorCheck()
{
    if (count < 10)
    {
        distanceArr[count] = distance;
        count++;
    }
    else
    {
        for (int i = 0; i < sizeof(distanceArr) - 1; i++)
        {
            distanceArr[i] = distanceArr[i + 1];
        }
    }
}