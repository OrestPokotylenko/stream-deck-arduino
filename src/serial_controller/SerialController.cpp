#include <Arduino.h>
#include "SerialController.h"
#include <ReceiverUtility.h>

SerialController::SerialController() : lastSong{"", ""}, hasNewData(false), inputBuffer(""), lastDataTime(0)
{
}

Song SerialController::getSong()
{
    return lastSong;
}

bool SerialController::hasNewSongData()
{
    return hasNewData;
}

void SerialController::clearNewDataFlag()
{
    hasNewData = false;
}

void SerialController::update()
{
    // Check for new serial data without blocking
    while (Serial.available()) {
        char c = Serial.read();
        
        if (c == '\n' || c == '\r') {
            if (inputBuffer.length() > 0) {
                processSongData();
                inputBuffer = "";
            }
        } else {
            inputBuffer += c;
            lastDataTime = millis();
        }
    }
    
    // Clear buffer if data is incomplete and timeout exceeded (prevent buffer overflow)
    if (inputBuffer.length() > 0 && (millis() - lastDataTime > 10000)) {
        inputBuffer = "";
    }
}

void SerialController::processSongData()
{
    static bool expectingDuration = false;
    static String tempSongName = "";
    
    String cleanData = ReceiverUtility::getCleanString(inputBuffer);
    
    if (cleanData.length() == 0) {
        return;
    }
    
    if (!expectingDuration) {
        // First line should be song name
        tempSongName = cleanData;
        expectingDuration = true;
    } else {
        // Second line should be duration
        if (tempSongName.length() > 0) {
            lastSong.name = tempSongName;
            lastSong.duration = cleanData;
            hasNewData = true;
        }
        expectingDuration = false;
        tempSongName = "";
    }
}

String SerialController::readLineWithTimeout(unsigned long timeoutMs) {
    String line = "";
    unsigned long start = millis();
    while (millis() - start < timeoutMs) {
        if (Serial.available()) {
            char c = Serial.read();
            if (c == '\n') {
                return line;
            }
            line += c;
            start = millis();  // reset timeout for each new byte
        }
    }
    return ""; // timeout
}

void SerialController::writeToSerial(String input) {
    Serial.println(input);
}

bool SerialController::waitForSerial(unsigned long timeoutMs) {
    unsigned long start = millis();
    while (!Serial.available()) {
        if (millis() - start >= timeoutMs) {
            return false;
        }
    }

    return true;
}