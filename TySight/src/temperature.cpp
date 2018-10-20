#include <temperature.h>

// Constructor to set the pins for the temperature module
Temperature::Temperature(int dataPin, int deadPin)
{
    this->dataPin = dataPin;
    this->deadPin = deadPin;
}

// Accessor for temperature
int Temperature::getTemperature()
{
    // Receive analog temp value
    analogVal = analogRead(dataPin);

    resistance = (float) (1023-analogVal)*10000/analogVal;
    temperature = 1/(log(resistance/10000)/thermistorVal+1/298.15)-273.15;
}

