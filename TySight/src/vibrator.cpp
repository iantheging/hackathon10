#include <vibrator.h>

Vibrator::Vibrator(int analogInPin, int analogOutPin)
{
    this->analogInPin = analogInPin;
    this->analogOutPin = analogOutPin;
}

void Vibrator::vibrate(int distance)
{
    // creates a strength value for analog output
    int strength = map(distance, 0, 50, 0, 255);
    analogWrite(analogOutPin, strength);
}