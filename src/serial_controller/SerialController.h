#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H

#include "include/Song.h"

class SerialController {
    public:
        SerialController();
        Song getSong();
        void writeToSerial(String input);
        bool hasNewSongData();
        void clearNewDataFlag();
        void update(); // Call this in loop to check for new data
        bool processNewSongData(); // Returns true if new data was processed

    private:
        bool waitForSerial(unsigned long timeoutMs);
        String readLineWithTimeout(unsigned long timeoutMs);
        void processSongData();
        
        Song lastSong;
        bool hasNewData;
        String inputBuffer;
        unsigned long lastDataTime;
};

#endif