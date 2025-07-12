#include <Arduino.h>
#include "SerialController.h"
#include <ReceiverUtility.h>

SerialController::SerialController()
{
}

Song SerialController::getSong()
{
    Song song;

    // Flush any old data
    while (Serial.available())
        Serial.read();

    // Wait until something comes
    while (!Serial.available());

    String songName = Serial.readStringUntil('\n');

    songName = ReceiverUtility::getCleanString(songName);

    while (!Serial.available());

    String durLine = Serial.readStringUntil('\n');

    song = {songName, durLine};

    return song;
}