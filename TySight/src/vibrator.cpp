#include <vibrator.h>

Vibrator::Vibrator(int analogOutPin)
{
    this->analogOutPin = analogOutPin;
}

void Vibrator::vibrate(int distance)
{
    // creates a strength value for analog output
    // inverted strength so it is stronger for closer objects
    int strength = map(distance, 0, 50, 150, 0);
    analogWrite(analogOutPin, strength);
}