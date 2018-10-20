#include <vibrator.h>

Vibrator::Vibrator(int analogOutPin)
{
    this->analogOutPin = analogOutPin;
}

void Vibrator::vibrate(int distance)
{
    // creates a strength value for analog output
    int strength = map(distance, 0, 100, 153, 0);
    analogWrite(analogOutPin, strength);
}