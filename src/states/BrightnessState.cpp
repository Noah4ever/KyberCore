#include "states/BrightnessState.hpp"
#include "events/EventBus.hpp"
#include "events/EventType.hpp"
#include "Arduino.h"
#include "ui/elements/DefaultSettingView.hpp"
#include "ui/elements/MenuList.hpp"

#include <cmath>

BrightnessState::BrightnessState() : brightnessLevel(DEFAULT_BRIGHTNESS), targetBrightnessLevel(DEFAULT_BRIGHTNESS), startBrightnessLevel(DEFAULT_BRIGHTNESS), animationProgress(1.0f), isAnimating(false) {
    defaultUI = new DefaultSettingView("Brightness");
    progressBar = new ProgressBar(brightnessLevel, MIN_BRIGHTNESS, MAX_BRIGHTNESS, 120, 10);
    progressBar->setValue(brightnessLevel);
    progressBar->x = 4;
    progressBar->y = 18;
    defaultUI->addChild(progressBar);

    menuUI = new MenuList();
}

void BrightnessState::handleRotation(int delta) {
    if (!isAnimating) {
        startBrightnessLevel = brightnessLevel;
        targetBrightnessLevel += delta * ROTATION_STEP;
        targetBrightnessLevel = std::fmax(MIN_BRIGHTNESS, std::fmin(MAX_BRIGHTNESS, targetBrightnessLevel));
        animationProgress = 0.0f;
        isAnimating = true;

        Event requestUI(EventType::DISPLAY_REQUEST_UPDATE, DataType::NONE);
        EventBus::getInstance().publish(requestUI);
    } else {
        targetBrightnessLevel += delta * ROTATION_STEP;
        targetBrightnessLevel = std::fmax(MIN_BRIGHTNESS, std::fmin(MAX_BRIGHTNESS, targetBrightnessLevel));
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
            publishBrightnessEvent();
            
            Event requestUI(EventType::DISPLAY_REQUEST_UPDATE, DataType::NONE);
            EventBus::getInstance().publish(requestUI);
        } else {
            brightnessLevel = lerpBrightness(startBrightnessLevel, targetBrightnessLevel, animationProgress);
            publishBrightnessEvent();
        }
    }
}

void BrightnessState::handleButtonPress() {
    // Implement button press behavior if needed
}

void BrightnessState::resetState() {
    brightnessLevel = DEFAULT_BRIGHTNESS;
    targetBrightnessLevel = DEFAULT_BRIGHTNESS;
    startBrightnessLevel = DEFAULT_BRIGHTNESS;
    animationProgress = 1.0f;
    isAnimating = false;
}

void BrightnessState::updateDisplay(IDisplay *display) {
    if (display) {
        progressBar->setValue(brightnessLevel);
        progressBar->clear(*display); // Only clears when new value is lower than the previous one
        progressBar->draw(*display);
        display->displayInternal();
    }
}

UIElement* BrightnessState::getDefaultUI() {
    return defaultUI;
}

UIElement* BrightnessState::getMenuUI() {
    return menuUI;
}

const uint8_t BrightnessState::icon_brightness[] PROGMEM = {
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row  0
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row  1
    0b00000000, 0b10000000, 0b00000001, 0b00000000, // Row  2
    0b00000000, 0b11000000, 0b00000011, 0b00000000, // Row  3
    0b00000000, 0b01100000, 0b00000110, 0b00000000, // Row  4
    0b00000000, 0b01100000, 0b00000110, 0b00000000, // Row  5
    0b00000000, 0b00110000, 0b00001100, 0b00000000, // Row  6
    0b00000000, 0b00010000, 0b00001000, 0b00000000, // Row  7
    0b00110000, 0b00000011, 0b11000000, 0b00001100, // Row  8
    0b00011000, 0b00001111, 0b11110000, 0b00011000, // Row  9
    0b00001110, 0b00011111, 0b11111000, 0b01110000, // Row 10
    0b00000111, 0b00111111, 0b11111100, 0b11100000, // Row 11
    0b00000000, 0b01111111, 0b11111110, 0b00000000, // Row 12
    0b00000000, 0b01111111, 0b11111110, 0b00000000, // Row 13
    0b00000000, 0b11111111, 0b11111111, 0b00000000, // Row 14
    0b00111110, 0b11111111, 0b11111111, 0b01111100, // Row 15
    0b00111110, 0b11111001, 0b10011111, 0b01111100, // Row 16
    0b00000000, 0b11111001, 0b10011111, 0b00000000, // Row 17
    0b00000000, 0b11111001, 0b10011111, 0b00000000, // Row 18
    0b00000010, 0b01111001, 0b10011110, 0b01000000, // Row 19
    0b00000110, 0b00111100, 0b00111100, 0b01100000, // Row 20
    0b00001100, 0b00011100, 0b00111000, 0b00110000, // Row 21
    0b00001000, 0b00001100, 0b00110000, 0b00010000, // Row 22
    0b00000000, 0b00001100, 0b00110000, 0b00000000, // Row 23
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row 24
    0b00000000, 0b00000111, 0b11100000, 0b00000000, // Row 25
    0b00000000, 0b00000011, 0b11000000, 0b00000000, // Row 26
    0b00000000, 0b00000111, 0b11100000, 0b00000000, // Row 27
    0b00000000, 0b00000001, 0b10000000, 0b00000000, // Row 28
    0b00000000, 0b00000001, 0b10000000, 0b00000000, // Row 29
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row 30
    0b00000000, 0b00000000, 0b00000000, 0b00000000  // Row 31
};
