#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <math.h>
#include <Arduino.h>

class Temperature
{
  private:
    // Pin values
    int dataPin;
    int deadPin; // Wire with no data running in (hardware required)

    float resistance;
    float temperature;
    int analogVal;
    int thermistorVal = 3975;

  public:
    // Constructor
    Temperature(int dataPin, int deadPin);

    // Accessor for temperature celcius
    float getTemperatureC();

    // Accessor for temperature fahrenheit 
    float getTemperatureF();
};

#endif