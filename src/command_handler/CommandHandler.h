#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <Arduino.h>
#include "enums/CommandType.h"
#include "include/PinCommand.h"

class CommandHandler
{
public:
    CommandHandler(uint8_t pauseButton, uint8_t nextTrackButton, uint8_t previousTrackButton);
    CommandType getCommandType();
    void update(); // Call this in the main loop to update button states

private:
    uint8_t pauseButton;
    uint8_t nextTrackButton;
    uint8_t previousTrackButton;
    
    // Debouncing variables
    bool lastButtonStates[3] = {false, false, false}; // Last stable states
    bool currentButtonStates[3] = {false, false, false}; // Current readings
    unsigned long lastDebounceTime[3] = {0, 0, 0}; // Last time buttons changed
    unsigned long debounceDelay = 50; // 50ms debounce delay
    CommandType pendingCommand = CommandType::NONE;
    
    static constexpr PinCommand pinMappings[3] = {
        {8, CommandType::NEXT_TRACK},
        {6, CommandType::PREVIOUS_TRACK},
        {7, CommandType::PLAY_PAUSE}};
        
    bool isButtonPressed(uint8_t buttonIndex);
};

#endif