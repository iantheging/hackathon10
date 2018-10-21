#include <Arduino.h>
#include <constants.h>
#include <button.h>

Button::Button(int buttonData)
{
    this->buttonData = buttonData;
}

int Button::getButtonPress()
{
    buttonState = digitalRead(buttonData);
    delay(75);
    if(digitalRead(buttonData) == buttonState && buttonState != 0){
        // Set to "hold button" mode
        return 2;
    }
    else{
        return buttonState;
    }
}
