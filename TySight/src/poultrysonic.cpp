#include <poultrysonic.h>
#include <temperature.h>

Poultrysonic::Poultrysonic(int trigPin, int echoPin, float temperature)
{
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->temperature = temperature;
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

    // Calculate the speed of sound based on the temperature
    speedOfSound = 331 + 0.6 * temperature;

    // Calculate the distance based on the temperature
    distance = duration * (speedOfSound / 10000.0) / 2.0;

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
        if (distance > avgDist + buffer || distance < avgDist - buffer || distance > 500)
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
