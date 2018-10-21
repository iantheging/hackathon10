#include <vibrator.h>
#include <constants.h>

Vibrator::Vibrator(int analogOutPinOne, int analogOutPinTwo)
{
    this->analogOutPinOne = analogOutPinOne;
    this->analogOutPinTwo = analogOutPinTwo;
}

void Vibrator::vibrate(int distance, int maxDistance, int strengthMax)
{
    // creates a strength value for analog output 154
    int strength = map(distance, 0, maxDistance, strengthMax, 0);

    if(distance > 55){
        strength = 0;
    }
    
    analogWrite(analogOutPinOne, strength);
    analogWrite(analogOutPinTwo, strength);
}

void Vibrator::vibrateAdjust(int strength)
{
    // Runs the motors at the given strength
    analogWrite(analogOutPinOne, strength);
    analogWrite(analogOutPinTwo, strength);
}