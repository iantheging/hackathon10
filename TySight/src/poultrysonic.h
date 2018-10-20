#include <Arduino.h>

#ifndef POULTRYSONIC_H
#define POULTRYSONIC_H

class Poultrysonic
{
  private:
    const int buffer = 20;

    // defines variables
    long duration;
    int distance;
    int count = 0;
    int distanceArr[10];
    int avgDist;
    int trigPin;
    int echoPin;
    float temperature;
    float speedOfSound;

  public:
    
    // constructor
    Poultrysonic(int trigPin, int echoPin, float temperature);

    // calculates the distance in centimeters
    int getDistance();

    // checks to ensure that distance is not outlier
    void errorCheck();
};

#endif