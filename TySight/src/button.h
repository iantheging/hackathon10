#ifndef BUTTON_H
#define BUTTON_H

class Button
{
  private:
    int buttonData;
    int buttonState;

  public:

    Button(int buttonData);

    int getButtonPress();
};

#endif