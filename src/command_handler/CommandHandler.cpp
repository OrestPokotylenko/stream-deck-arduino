#include "CommandHandler.h"

constexpr PinCommand CommandHandler::pinMappings[];

CommandHandler::CommandHandler(uint8_t pauseButton, uint8_t nextTrackButton, uint8_t previousTrackButton)
    : pauseButton(pauseButton), nextTrackButton(nextTrackButton), previousTrackButton(previousTrackButton)
{
    // Initialize all button states as not pressed (HIGH due to INPUT_PULLUP)
    for (int i = 0; i < 3; i++)
    {
        lastButtonStates[i] = true; // HIGH = not pressed with pullup
        currentButtonStates[i] = true;
        lastDebounceTime[i] = 0;
    }
}

void CommandHandler::update()
{
    for (int i = 0; i < 3; i++)
    {
        bool reading = digitalRead(pinMappings[i].pin);

        if (reading != currentButtonStates[i])
        {
            lastDebounceTime[i] = millis();
            currentButtonStates[i] = reading;
        }

        // If not enough time has passed since the last change
        if ((millis() - lastDebounceTime[i]) <= debounceDelay)
        {
            continue;
        }

        // If the button state did not change
        if (currentButtonStates[i] == lastButtonStates[i])
        {
            continue;
        }

        lastButtonStates[i] = currentButtonStates[i];

        // Check for button press (transition from HIGH to LOW with pullup)
        if (currentButtonStates[i] == LOW)
        {
            pendingCommand = pinMappings[i].commandType;
        }
    }
}

CommandType CommandHandler::getCommandType()
{
    CommandType command = pendingCommand;
    pendingCommand = CommandType::NONE; // Clear after reading
    return command;
}

bool CommandHandler::isButtonPressed(uint8_t buttonIndex)
{
    return lastButtonStates[buttonIndex] == LOW;
}