#include <Arduino.h>
#include <poultrysonic.h>

Poultrysonic::Poultrysonic(int trigPin, int echoPin)
{
    this->trigPin = trigPin;
    this->echoPin = echoPin;
}

int Poultrysonic::getDistance()
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

    // checks for outliers
    errorCheck();

    return distance;
}

void Poultrysonic::errorCheck()
{
    // fills the array
    if (count < 10)
    {
        distanceArr[count] = distance;
        count++;
    }
    // runs after the array has been filled
    else
    {
        // checks if distance is outside the margin of error
        if (distance > avgDist + buffer || distance < avgDist - buffer)
        {
            distance = avgDist;
        }
        else
        {
            // moves all values down a position
            for (int i = 0; i < sizeof(distanceArr) - 1; i++)
            {
                distanceArr[i] = distanceArr[i + 1];
            }
            distanceArr[9] = distance;

            // calculating new average
            int sum = 0;
            for (int j = 0; j < sizeof(distanceArr); j++)
            {
                sum += distanceArr[j];
            }
            avgDist = sum / 10;
        }
    }
}
