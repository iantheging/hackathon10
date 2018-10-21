#include <Arduino.h>
#include <poultrysonic.h>
#include <constants.h>

#ifndef VIBRATOR_H
#define VIBRATOR_H

class Vibrator
{
  private:
    int analogOutPinOne;
    int analogOutPinTwo;
    int topValue;
    float strength;

  public:

    Vibrator(int analogOutPinOne, int analogOutPinTwo);

    void vibrate(int distance, int maxDistance, int strengthMax);

    void vibrateAdjust(int strengthMax);
};

#endif