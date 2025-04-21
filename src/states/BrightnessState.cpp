#include "states/BrightnessState.hpp"
#include "events/EventBus.hpp"
#include "events/EventType.hpp"
#include "Arduino.h" // For Serial print
#include <cmath>

BrightnessState::BrightnessState() : brightnessLevel(DEFAULT_BRIGHTNESS), targetBrightnessLevel(DEFAULT_BRIGHTNESS), startBrightnessLevel(DEFAULT_BRIGHTNESS), animationProgress(1.0f), isAnimating(false) {}

void BrightnessState::handleRotation(int delta) {
    if (!isAnimating) {
        startBrightnessLevel = brightnessLevel;
        targetBrightnessLevel += delta * ROTATION_STEP;
        targetBrightnessLevel = std::fmax(MIN_BRIGHTNESS, std::fmin(MAX_BRIGHTNESS, targetBrightnessLevel));
        animationProgress = 0.0f;
        isAnimating = true;
    }
}

int BrightnessState::lerpBrightness(int a, int b, float t) {
    return static_cast<int>(a + (b - a) * t);
}

void BrightnessState::update() {
    if (isAnimating) {
        animationProgress += ANIMATION_SPEED;
        if (animationProgress >= 1.0f) {
            animationProgress = 1.0f;
            isAnimating = false;
            brightnessLevel = targetBrightnessLevel;
            Event brightnessEvent(EventType::BRIGHTNESS_CHANGED, DataType::INT);
            brightnessEvent.intData.value = brightnessLevel;
            EventBus::getInstance().publish(brightnessEvent);
        } else {
            brightnessLevel = lerpBrightness(startBrightnessLevel, targetBrightnessLevel, animationProgress);
            Event brightnessEvent(EventType::BRIGHTNESS_CHANGED, DataType::INT);
            brightnessEvent.intData.value = brightnessLevel;
            EventBus::getInstance().publish(brightnessEvent);
        }
    }
}

void BrightnessState::handleButtonPress() {

}

void BrightnessState::updateDisplay(IDisplay* display) {
    if (display) {
        display->clear();
        display->drawString(0, 0, "Brightness");
        // display->drawProgressBar(0, 10, 128, 8, static_cast<int>(static_cast<float>(brightnessLevel) / MAX_BRIGHTNESS * 100)); // Angepasste ProgressBar
        display->display();
    }
}

void BrightnessState::resetState() {
    brightnessLevel = DEFAULT_BRIGHTNESS;
    targetBrightnessLevel = DEFAULT_BRIGHTNESS;
    startBrightnessLevel = DEFAULT_BRIGHTNESS;
    animationProgress = 1.0f;
    isAnimating = false;
}