#include <Arduino.h>
#include <temperature.h>
#include <constants.h>
#include <stdlib.h>


#ifndef POULTRYSONIC_H
#define POULTRYSONIC_H


class Poultrysonic
{
  private:
    const int buffer = 20;

    // defines variables
    long duration;
    int distance;
    int count;
    int distanceSum;
    int avgDist;
    int trigPin;
    int echoPin;
    float temperature;
    float speedOfSound;
    int lastDistance;
    int currentDistance;
    int distanceArr[3];


    

  public:
    

    // constructor
    Poultrysonic(int trigPin, int echoPin, float temperature);

    // calculates the distance in centimeters
    int getDistance(int maxDistance);

    // Ensures data stays within the confined parameters
    void errorAvoid(int maxDistance);

};

#endif