#include "ScreenController.h"

ScreenController::ScreenController(LiquidCrystal &lcd)
    : _lcd(lcd)
{
}

void ScreenController::setContent(Song song) {
    if (!isContentChanged(song)) {
        return;
    }

    if (song.name.length() == 0 && song.duration.length() == 0) {
        return;
    }

    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print(song.name);
    _lcd.setCursor(0, 1);
    _lcd.print(song.duration);
}

bool ScreenController::isContentChanged(Song song) {
    if (lastName != song.name || lastDuration != song.duration) {
        lastName = song.name;
        lastDuration = song.duration;
        return true;
    }
    
    return false;
}