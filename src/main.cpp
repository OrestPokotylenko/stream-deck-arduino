#include <Arduino.h>
#include <LiquidCrystal.h>
#include "screen_controller/ScreenController.h"
#include "serial_controller/SerialController.h"
#include "config.h"

#include "app_communicator/AppCommunicator.h"
#include "command_handler/CommandHandler.h"

LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
ScreenController screen(lcd);
SerialController serialController;

CommandHandler commandHandler(PAUSE_BUTTON, NEXT_TRACK_BUTTON, PREVIOUS_TRACK_BUTTON);
AppCommunicator appCommunicator(commandHandler, serialController);

void setup()
{
    pinMode(PAUSE_BUTTON, INPUT_PULLUP);
    pinMode(NEXT_TRACK_BUTTON, INPUT_PULLUP);
    pinMode(PREVIOUS_TRACK_BUTTON, INPUT_PULLUP);
    lcd.begin(LCD_COLUMNS, LCD_ROWS);
    Serial.begin(BAUD_RATE);
}

void loop()
{
    // Update command handler to process button debouncing
    commandHandler.update();
    
    // Update serial controller to check for new data
    serialController.update();
    
    if (serialController.processNewSongData()) {
        screen.setContent(serialController.getSong());
    }
    
    appCommunicator.sendCommand();
}