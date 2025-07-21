#include "VolumeController.h"

VolumeController::VolumeController(uint8_t volumePotentiometer)
    : volumePotentiometer(volumePotentiometer), currentVolume(0), rawVolume(0), 
      lastSentVolume(-1), lastVolumeChangeTime(0), volumeReadyToSend(false)
{
}

int VolumeController::calculateVolume(int rawValue) const
{
    // Use calibrated range for better accuracy
    int volume = map(rawValue, POT_MIN, POT_MAX, 0, 100);
    return constrain(volume, 0, 100);
}

int VolumeController::getVolume() const
{
    return currentVolume;
}

bool VolumeController::hasVolumeChanged()
{
    // Check if volume has settled (no changes for VOLUME_SETTLE_DELAY ms)
    if (volumeReadyToSend && currentVolume != lastSentVolume) {
        lastSentVolume = currentVolume; // Update what we've sent
        volumeReadyToSend = false; // Reset flag
        return true; // Volume has changed and settled
    }
    return false; // No settled volume change
}

void VolumeController::update()
{
    int rawValue = analogRead(volumePotentiometer);

    if (abs(rawValue - rawVolume) >= VOLUME_THRESHOLD)
    {
        updateVolume(rawValue);
    }
    
    // Check if volume has settled (stopped changing for the settle delay)
    if (!volumeReadyToSend && lastVolumeChangeTime > 0 && 
        (millis() - lastVolumeChangeTime) >= VOLUME_SETTLE_DELAY) {
        volumeReadyToSend = true; // Volume has settled, ready to send
    }
}

void VolumeController::updateVolume(int rawValue)
{
    rawVolume = rawValue;
    currentVolume = calculateVolume(rawVolume);
    lastVolumeChangeTime = millis(); // Record when volume changed
    volumeReadyToSend = false; // Volume is changing, not ready to send yet
}