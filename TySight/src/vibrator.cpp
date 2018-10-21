#include <vibrator.h>
#include <constants.h>

Vibrator::Vibrator(int analogOutPinOne, int analogOutPinTwo)
{
    this->analogOutPinOne = analogOutPinOne;
    this->analogOutPinTwo = analogOutPinTwo;
}

void Vibrator::vibrate(int distance, int maxDistance)
{
    // creates a strength value for analog output 154
    int strength = map(distance, 0, maxDistance, 154, 0);
    analogWrite(analogOutPinOne, strength);
    analogWrite(analogOutPinTwo, strength);
    Serial.print("Strength: ");
    Serial.println(strength);
}

void Vibrator::vibrateAdjust(int strength)
{
    // Runs the motors at the given strength
    analogWrite(analogOutPinOne, strength);
    analogWrite(analogOutPinTwo, strength);
}