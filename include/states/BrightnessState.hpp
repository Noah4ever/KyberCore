#pragma once

#include "states/SettingState.hpp"
#include "components/display/IDisplay.hpp"
#include "events/EventType.hpp"
#include "ui/elements/ProgressBar.hpp"

class BrightnessState : public SettingState
{
private:
    int brightnessLevel;
    int targetBrightnessLevel;
    int startBrightnessLevel;
    float animationProgress;
    bool isAnimating;

    constexpr static int DEFAULT_BRIGHTNESS = 50;
    constexpr static int ROTATION_STEP = 4;
    constexpr static float ANIMATION_SPEED = 0.05f;
    constexpr static int MIN_BRIGHTNESS = 0;
    constexpr static int MAX_BRIGHTNESS = 255;

    UIElement *defaultUI;
    UIElement *menuUI;
    ProgressBar *progressBar;

    int lerpBrightness(int a, int b, float t);
    void publishBrightnessEvent()
    {
        Event brightnessEvent(EventType::BRIGHTNESS_CHANGED, DataType::INT);
        brightnessEvent.intData.value = brightnessLevel;
        EventBus::getInstance().publish(brightnessEvent);
    }

public:
    BrightnessState();

    void handleRotation(int delta) override;
    void handleButtonPress() override;
    void update() override;
    void resetState() override;

    void updateDisplay(IDisplay *display) override;
    UIElement *getDefaultUI() override;
    UIElement *getMenuUI() override;

    // Static members for the brightness icon
    static const uint8_t icon_brightness[];
    static const int ICON_BRIGHTNESS_WIDTH = 32;
    static const int ICON_BRIGHTNESS_HEIGHT = 32;
};