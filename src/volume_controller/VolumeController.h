#ifndef VOLUME_CONTROLLER_H
#define VOLUME_CONTROLLER_H

#include <Arduino.h>

class VolumeController
{
    public:
        VolumeController(uint8_t volumePotentiometer);
        void update();
        int getVolume() const;
        bool hasVolumeChanged(); // Returns true if volume changed since last check

    private:
        uint8_t volumePotentiometer;
        int currentVolume;
        int rawVolume;
        int lastSentVolume; // Track what volume was last sent
        unsigned long lastVolumeChangeTime; // When volume last changed
        bool volumeReadyToSend; // True when volume has settled

        constexpr static int VOLUME_THRESHOLD = 10;
        constexpr static unsigned long VOLUME_SETTLE_DELAY = 300; // Wait 300ms after last change
        
        // Calibration values - adjust these for your specific potentiometer
        constexpr static int POT_MIN = 0;    // Minimum reliable reading
        constexpr static int POT_MAX = 1000; // Maximum reliable reading (usually ~1000 instead of 1023)

        int calculateVolume(int rawValue) const;
        void updateVolume(int rawValue);

};

#endif