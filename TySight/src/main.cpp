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
int alarmMode = 3;

int toggle = 1;
int buttonHold = 2;
int noPress = 0;

int maxDistance = 300;

int buttonPress;

int arr[10];

int ax;
int ay;
int az;

int adjustedAx;

int strengthMax;
int strengthTwo;

// Create instance of Poultrysonic
Poultrysonic ps(TRIG_PIN, ECHO_PIN, temperature);

// Create new instance of vibrator
Vibrator vib(ANALOG_OUT_ONE, ANALOG_OUT_TWO);

// Create instance of Temperature
Temperature temp(DATA_PIN, DEAD_PIN);

// Create instance of Button
Button butt(BUTTON_DATA, BUTTONTWO);

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

    // initialize the pushbutton pin 4 as an input:
    pinMode(BUTTONTWO, INPUT);

    // Set buzzer - pin 11 as an output
    pinMode(BUZZER_PIN, OUTPUT);

    Serial.begin(9600); // Starts the serial communication

    // Poll initial temperature once
    temperature = temp.getTemperatureC();
}

void loop()
{
    // Retrieve current button press (if any)
    buttonPress = butt.getButtonPress();

    if (buttonPress == alarmMode)
    {
        while (1)
        {
            // Sound the alarm
            tone(BUZZER_PIN, 1000); // Send 1KHz sound signal...
            delay(500);        // ...for 1/2 sec
            noTone(BUZZER_PIN);     // Stop sound...
            delay(200);        // ...for 1/2 sec
            tone(BUZZER_PIN, 1500); // Send 1.5KHz sound signal...
            delay(500); // For 1/2 seond
            noTone(BUZZER_PIN);     // Stop sound...
            delay(200);        // ...for 1/2 sec
        }
    }

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
        maxDistance = 75;

        // Returns distance from the ultrasonic sensor in cm
        distance = ps.getDistance(maxDistance);

        // Vibrates the motors for the distance amount
        vib.vibrate(distance, maxDistance, strengthMax);

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
        vib.vibrate(distance, maxDistance, strengthMax);

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
            strengthTwo = map(adjustedAx, 150, 0, 220, 0);
            vib.vibrateAdjust(strengthTwo);
            strengthMax = strengthTwo;
        }
        // Pulse twice to confirm selection
        vib.vibrateAdjust(0);
        delay(500);
        vib.vibrateAdjust(220);
        delay(700);
        vib.vibrateAdjust(0);
        delay(300);
        vib.vibrateAdjust(220);
        delay(700);
        vib.vibrateAdjust(0);
        delay(300);
        MMA7660.wireKill();
    }
}