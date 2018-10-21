#include <poultrysonic.h>

Poultrysonic::Poultrysonic(int trigPin, int echoPin, float temperature)
{
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->temperature = temperature;
    count = 0;
    lastDistance = 0;
}

int Poultrysonic::getDistance(int maxDistance)
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
    distance = duration * ((speedOfSound / 10000.0) / 2.0);

    // checks for outliers
    //errorCheck();

    errorAvoid(maxDistance);

    return distance;
}

void Poultrysonic::errorAvoid(int maxDistance){
    // Do not allow distances past max_distance 
    if(distance > maxDistance){
        distance = maxDistance;
    }

}


