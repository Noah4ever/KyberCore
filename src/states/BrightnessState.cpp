
#include "states/BrightnessState.hpp"

#include <cmath> 

BrightnessState::BrightnessState() : brightnessLevel(DEFAULT_BRIGHTNESS) {}

void BrightnessState::handleRotation(int delta) {
    brightnessLevel += delta * ROTATION_STEP;
    brightnessLevel = std::fmax(MIN_BRIGHTNESS, std::fmin(MAX_BRIGHTNESS, brightnessLevel));
}

void BrightnessState::handleButtonPress() {
    
}

void BrightnessState::updateDisplay(IDisplay* display) {
    if (display) {
        display->clear();
        display->drawString(0, 0, "Brightness");
        // display->drawProgressBar(0, 10, 128, 8, static_cast<int>(brightnessLevel * 100));
        display->display();
    }
}

void BrightnessState::resetState() {
    brightnessLevel = DEFAULT_BRIGHTNESS; // Reset to default value
}