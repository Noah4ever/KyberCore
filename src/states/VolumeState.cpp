
#include "states/VolumeState.hpp"
#include "events/EventBus.hpp"
#include "events/EventType.hpp"
#include "Arduino.h" // For Serial print
#include "ui/elements/DefaultSettingView.hpp"
#include "ui/elements/ProgressBar.hpp"
#include "ui/elements/MenuList.hpp"
#include <cmath>

VolumeState::VolumeState() : volumeLevel(DEFAULT_VOLUME) {
    defaultUI = new DefaultSettingView("Volume");
    progressBar = new ProgressBar(volumeLevel, MIN_VOLUME, MAX_VOLUME, 120, 10);
    progressBar->setValue(volumeLevel);
    progressBar->x = 4;
    progressBar->y = 18;
    defaultUI->addChild(progressBar);

    menuUI = new MenuList();
}

void VolumeState::handleRotation(int delta)
{
    volumeLevel += delta * ROTATION_STEP;
    volumeLevel = std::fmax(MIN_VOLUME, std::fmin(MAX_VOLUME, volumeLevel));

    publishVolumeEvent();

    Event requestUI(EventType::DISPLAY_REQUEST_UPDATE, DataType::NONE);
    EventBus::getInstance().publish(requestUI);

    Event rainbowEvent(EventType::BLADE_RAINBOW_ANIMATION, DataType::NONE);
    EventBus::getInstance().publish(rainbowEvent);
}

void VolumeState::handleButtonPress()
{
}

void VolumeState::update()
{
    // Update logic if needed
}

void VolumeState::updateDisplay(IDisplay *display)
{
    if (display)
    {
        progressBar->setValue(volumeLevel);
        progressBar->clear(*display);
        progressBar->draw(*display);
        display->displayInternal();
    }
}

UIElement *VolumeState::getDefaultUI()
{
    return defaultUI;
}

UIElement *VolumeState::getMenuUI()
{
    return menuUI;
}

void VolumeState::resetState()
{
    volumeLevel = DEFAULT_VOLUME; // Reset to default value
}

// 32×32 volume icon for SSD1306
const uint8_t VolumeState::icon_volume[] PROGMEM = {
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row  0
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row  1
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row  2
    0b00000000, 0b00000011, 0b00000000, 0b00000000, // Row  3
    0b00000000, 0b00000011, 0b10000000, 0b00000000, // Row  4
    0b00000000, 0b00000011, 0b10000000, 0b11000000, // Row  5
    0b00000000, 0b00001011, 0b10000000, 0b11100000, // Row  6
    0b00000000, 0b00011011, 0b10000000, 0b01110000, // Row  7
    0b00000000, 0b00111011, 0b10000000, 0b00111000, // Row  8
    0b00000000, 0b01111011, 0b10000110, 0b00111000, // Row  9
    0b00000000, 0b11111011, 0b10000111, 0b00011100, // Row 10
    0b00011111, 0b11111011, 0b11100011, 0b00001100, // Row 11
    0b00111111, 0b11111011, 0b11110011, 0b10001100, // Row 12
    0b00111111, 0b11111011, 0b11110001, 0b10001100, // Row 13
    0b00111111, 0b11111011, 0b11110001, 0b10001100, // Row 14
    0b00111111, 0b11111011, 0b11110011, 0b10001100, // Row 15
    0b00011111, 0b11111011, 0b11100011, 0b10001100, // Row 16
    0b00000000, 0b11111011, 0b10000111, 0b00011100, // Row 17
    0b00000000, 0b01111011, 0b10000110, 0b00111000, // Row 18
    0b00000000, 0b00111011, 0b10000000, 0b00111000, // Row 19
    0b00000000, 0b00011011, 0b10000000, 0b01110000, // Row 20
    0b00000000, 0b00001011, 0b10000000, 0b11100000, // Row 21
    0b00000000, 0b00000011, 0b10000000, 0b11000000, // Row 22
    0b00000000, 0b00000011, 0b10000000, 0b00000000, // Row 23
    0b00000000, 0b00000011, 0b00000000, 0b00000000, // Row 24
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row 25
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row 26
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row 27
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row 28
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row 29
    0b00000000, 0b00000000, 0b00000000, 0b00000000, // Row 30
    0b00000000, 0b00000000, 0b00000000, 0b00000000  // Row 31
};
