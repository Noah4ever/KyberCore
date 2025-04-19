
#include "states/VolumeState.hpp"

#include <cmath> 

VolumeState::VolumeState() : volumeLevel(DEFAULT_VOLUME) {}

void VolumeState::handleRotation(int delta) {
    volumeLevel += delta * ROTATION_STEP;
    volumeLevel = std::fmax(MIN_VOLUME, std::fmin(MAX_VOLUME, volumeLevel));

    // Update the display with the new volume level
    // publish an event to event bus 
}

void VolumeState::handleButtonPress() {
    
}

void VolumeState::updateDisplay(IDisplay* display) {
    if (display) {
        display->clear();
        display->drawString(0, 0, "Volume");
        // display->drawProgressBar(0, 10, 128, 8, static_cast<int>(volumeLevel * 100));
        display->display();
    }
}

void VolumeState::resetState() {
    volumeLevel = DEFAULT_VOLUME; // Reset to default value
}