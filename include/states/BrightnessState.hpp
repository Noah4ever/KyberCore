#pragma once

#include "states/SettingState.hpp"
#include "components/display/Display.hpp"

class BrightnessState : public SettingState
{
private:
    int brightnessLevel;
    int targetBrightnessLevel;
    int startBrightnessLevel;
    float animationProgress;
    bool isAnimating;

    constexpr static int DEFAULT_BRIGHTNESS = 50; // Default brightness level
    constexpr static int ROTATION_STEP = 5;       // Step size for brightness adjustment
    constexpr static float ANIMATION_SPEED = 0.05f; // Geschwindigkeit der Animation (anpassen)
    constexpr static int MIN_BRIGHTNESS = 0;      // Minimum brightness level
    constexpr static int MAX_BRIGHTNESS = 255;    // Maximum brightness level

    int lerpBrightness(int a, int b, float t);

public:
    BrightnessState();

    void handleRotation(int delta) override;
    void handleButtonPress() override;
    void update() override;
    void updateDisplay(IDisplay *display) override;
    void resetState() override;
};