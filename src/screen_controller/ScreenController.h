#ifndef sCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

#include <LiquidCrystal.h>
#include "include/Song.h"

class ScreenController {
    public:
        ScreenController(LiquidCrystal &lcd);
        void setContent(Song song);

    private:
        LiquidCrystal &_lcd;
        String lastName;
        String lastDuration;

        bool isContentChanged(Song song);
};

#endif