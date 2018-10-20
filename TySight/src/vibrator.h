#include <Arduino.h>

#ifndef VIBRATOR_H
#define VIBRATOR_H

class Vibrator
{
  private:
    int analogInPin;
    int analogOutPin;

  public:
    Vibrator(int analogInPin, int analogOutPin);

    void vibrate(int distance);
};

#endif