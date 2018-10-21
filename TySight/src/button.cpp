#include <Arduino.h>
#include <constants.h>
#include <button.h>

Button::Button(int buttonData, int buttonDataTwo)
{
    this->buttonData = buttonData;
    this->buttonDataTwo = buttonDataTwo;
}

int Button::getButtonPress()
{
    buttonState = digitalRead(buttonData);
    buttonStateTwo = digitalRead(buttonDataTwo);
    delay(75);
    if (digitalRead(buttonData) == buttonState && buttonState != 0)
    {
        // Set to "hold button" mode
        return 2;
    }
    else if (digitalRead(buttonDataTwo) == 1)
    {
        delay(500);
        // If button was held for half a second
        if (digitalRead(buttonDataTwo) == 1)
        {
            return 3;
        }
    }

    return buttonState;
}
