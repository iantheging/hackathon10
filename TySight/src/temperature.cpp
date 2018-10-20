#include <temperature.h>

// Constructor to set the pins for the temperature module
Temperature::Temperature(int dataPin, int deadPin)
{
    this->dataPin = dataPin;
    this->deadPin = deadPin;
}

// Accessor for temperature C
float Temperature::getTemperatureC()
{
    // Receive analog temp value
    analogVal = analogRead(dataPin);

    // Calculate temperature value in Celcius per the datasheet
    resistance = (float) (1023-analogVal)*10000/analogVal;
    temperature = 1/(log(resistance/10000)/thermistorVal+1/298.15)-273.15;

    return temperature;
}

// Accessor for temperature F
float Temperature::getTemperatureF()
{
    temperature = getTemperatureC();

    // Convert to fahrenheit 
    temperature = (9.0/5.0)*(temperature) + 32;

    return temperature;
}

