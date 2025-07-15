#include <Arduino.h>
#include <LiquidCrystal.h>
#include "screen_controller/ScreenController.h"
#include "serial_controller/SerialController.h"
#include "config.h"

#include "app_communicator/AppCommunicator.h"
#include "command_handler/CommandHandler.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
ScreenController screen(lcd);
SerialController serialController;

CommandHandler commandHandler(PAUSE_BUTTON, NEXT_TRACK_BUTTON, PREVIOUS_TRACK_BUTTON);
AppCommunicator appCommunicator(commandHandler, serialController);

void setup()
{
    pinMode(PAUSE_BUTTON, INPUT_PULLUP);
    pinMode(NEXT_TRACK_BUTTON, INPUT_PULLUP);
    pinMode(PREVIOUS_TRACK_BUTTON, INPUT_PULLUP);
    lcd.begin(16, 2);
    Serial.begin(115200);
}

void loop()
{
    // Update command handler to process button debouncing
    commandHandler.update();
    
    // Update serial controller to check for new data (non-blocking)
    serialController.update();
    
    // Only update screen if there's new song data
    if (serialController.hasNewSongData()) {
        screen.setContent(serialController.getSong());
        serialController.clearNewDataFlag(); // Clear flag after processing
    }
    
    appCommunicator.sendCommand();
}