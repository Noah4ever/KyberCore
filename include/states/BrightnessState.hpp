#pragma once

#include "states/SettingState.hpp"
#include "components/display/Display.hpp"

class BrightnessState : public SettingState
{
private:
    int brightnessLevel;
    constexpr static int DEFAULT_BRIGHTNESS = 50; // Default brightness level
    constexpr static int ROTATION_STEP = 1;       // Step size for brightness adjustment
    constexpr static int MIN_BRIGHTNESS = 0;      // Minimum brightness level
    constexpr static int MAX_BRIGHTNESS = 100;    // Maximum brightness level

public:
    BrightnessState();

    void handleRotation(int delta) override;
    void handleButtonPress() override;
    void updateDisplay(IDisplay *display) override;
    void resetState() override;
};
