#ifndef BUTTON_H
#define BUTTON_H

class Button
{
  private:
    int buttonData;
    int buttonDataTwo;
    int buttonState;
    int buttonStateTwo;
    int calibrated = 0;

  public:

    Button(int buttonData, int buttonDataTwo);

    int getButtonPress();
};

#endif