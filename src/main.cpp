#include <Arduino.h>
#include <LiquidCrystal.h>
#include "screen_controller/ScreenController.h"
#include "serial_controller/SerialController.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
ScreenController screen(lcd);
SerialController serialController;

void setup()
{
    lcd.begin(16, 2);
    Serial.begin(115200);
}

void loop()
{
    screen.setContent(serialController.getSong());
}