#include "ScreenController.h"

ScreenController::ScreenController(LiquidCrystal &lcd, int lcdWidth)
    : _lcd(lcd), scrollPosition(0), lastScrollTime(0), needsScrolling(false), currentSongName(""), lcdWidth(lcdWidth)
{
}

void ScreenController::setContent(Song song) {
    if (!isContentChanged(song)) {
        return;
    }

    if (song.name.length() == 0 && song.duration.length() == 0) {
        return;
    }

    // Store current song for scrolling
    currentSongName = song.name;
    
    // Reset scrolling state for new song
    scrollPosition = 0;
    lastScrollTime = millis();
    needsScrolling = (static_cast<int>(currentSongName.length()) > lcdWidth);

    _lcd.clear();
    
    _lcd.setCursor(0, 0);
    _lcd.print(getDisplayText());
    
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

void ScreenController::update() {
    if (needsScrolling) {
        updateScrollingText();
    }
}

void ScreenController::updateScrollingText() {
    unsigned long currentTime = millis();
    
    if (scrollPosition == 0 && (currentTime - lastScrollTime) < PAUSE_AT_START) {
        return;
    }
    
    if ((currentTime - lastScrollTime) >= SCROLL_DELAY) {
        scrollPosition++;
        
        int maxScroll = currentSongName.length() + 3;
        if (scrollPosition >= maxScroll) {
            scrollPosition = 0;
        }
        
        // Update display
        _lcd.setCursor(0, 0);
        _lcd.print(getDisplayText());
        
        lastScrollTime = currentTime;
    }
}

String ScreenController::getDisplayText() {
    if (!needsScrolling) {
        return currentSongName.substring(0, lcdWidth);
    }
    
    String scrollText = currentSongName + "   ";
    String displayText = "";
    
    for (int i = 0; i < lcdWidth; i++) {
        int charIndex = (scrollPosition + i) % scrollText.length();
        displayText += scrollText.charAt(charIndex);
    }
    
    return displayText;
}