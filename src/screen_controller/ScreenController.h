#ifndef sCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

#include <LiquidCrystal.h>
#include "include/Song.h"

class ScreenController {
    public:
        ScreenController(LiquidCrystal &lcd, int lcdWidth);
        void setContent(Song song);
        void update();

    private:
        LiquidCrystal &_lcd;
        String lastName;
        String lastDuration;
        
        // Scrolling variables
        int scrollPosition;
        unsigned long lastScrollTime;
        bool needsScrolling;
        String currentSongName;
        
        // Scrolling configuration
        int lcdWidth;
        static const unsigned long SCROLL_DELAY = 400; // ms between scroll steps
        static const unsigned long PAUSE_AT_START = 1500; // ms to pause at beginning

        bool isContentChanged(Song song);
        void updateScrollingText();
        String getDisplayText();
};

#endif