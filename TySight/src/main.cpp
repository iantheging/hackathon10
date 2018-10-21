#include <Arduino.h>
#include "poultrysonic.h"
#include "Temperature.h"
#include "vibrator.h"
#include "constants.h"
#include "button.h"
#include "MMA7660.h"

// defines variables
long duration;
int distance;
float temperature;
int mode = 0;

int mainMode = 0;
int modeOne = 1;
int modeTwo = 2;

int toggle = 1;
int buttonHold = 2;
int noPress = 0;

int maxDistance = 300;

int buttonPress;

int ax;
int ay;
int az;

int adjustedAy;

// Create instance of Poultrysonic
Poultrysonic ps(TRIG_PIN, ECHO_PIN, temperature);

// Create new instance of vibrator
Vibrator vib(ANALOG_OUT_ONE, ANALOG_OUT_TWO);

// Create instance of Temperature
Temperature temp(DATA_PIN, DEAD_PIN);

// Create instance of Button
Button butt(BUTTON_DATA);

void setup()
{
    // Set Poultrysonic pins directions
    pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
    pinMode(ECHO_PIN, INPUT);  // Sets the echoPin as an Input

    // Set Temperature pins direction
    pinMode(DATA_PIN, INPUT);

    // Set vibrate motor pin directions
    pinMode(ANALOG_OUT_ONE, OUTPUT);
    pinMode(ANALOG_OUT_TWO, OUTPUT);

    // Set button pin direction
    pinMode(BUTTON_DATA, INPUT);

    Serial.begin(9600); // Starts the serial communication

    // Poll initial temperature once
    temperature = temp.getTemperatureC();
}

void loop()
{
    // Retrieve current button press (if any)
    buttonPress = butt.getButtonPress();

    // Toggle mode of system based upon a button press
    // If no button press
    if (buttonPress == noPress)
    {
        // If previously in modeTwo, jump to main mode
        if (mode == modeTwo)
        {
            mode = mainMode;
        }
    }
    else
    {
        // If currently in the main mode
        if (mode == mainMode)
        {
            // If button press is a tap, toggle to mode one
            if (buttonPress == toggle)
            {
                mode = modeOne;
            }
            // If button press is a hold, jump to mode two
            if (buttonPress == buttonHold)
            {
                mode = modeTwo;
            }
        }
        // If currently in mode one
        else if (mode == modeOne)
        {
            // If button press is a tap, toggle to main mode
            if (buttonPress == toggle)
            {
                mode = modeOne;
            }
            // If button press is a hold, jump to mode two
            if (buttonPress == buttonHold)
            {
                mode = modeTwo;
            }
        }
    }

    // Main mode
    // Far range mode
    if (mode == mainMode)
    {
        maxDistance = 300;

        // Returns distance from the ultrasonic sensor in cm
        distance = ps.getDistance(maxDistance);

        // Vibrates the motors for the distance amount
        vib.vibrate(distance, maxDistance);

        // Prints the distance in the Serial Monitor
        Serial.print("Distance: ");
        Serial.println(distance);

        Serial.println();
    }
    // Mode One
    // Close range mode
    else if (mode == modeOne)
    {
        maxDistance = 150;

        // Returns distance from the ultrasonic sensor in cm
        distance = ps.getDistance(maxDistance);

        // Vibrates the motors for the distance amount
        vib.vibrate(distance, maxDistance);

        // Prints the distance in the Serial Monitor
        Serial.print("Distance: ");
        Serial.println(distance);

        Serial.println();
    }
    // Mode Two
    else
    {
        MMA7660.init();
        while (butt.getButtonPress() == buttonHold)
        {
            delay(100);
            MMA7660.getValues(&ax, &ay, &az);
            adjustedAx = ax + 80;
            int strengthTwo = map(adjustedAx, 150, 0, 220, 50);
            vib.vibrateAdjust(strengthTwo);
            Serial.print("Strength: ");
            Serial.println(strengthTwo);
            Serial.print("Adjusted: ");
            Serial.println(adjustedAx);
        }
        MMA7660.wireKill();
    }
}