#pragma once

#include "states/SettingState.hpp"
#include "components/display/IDisplay.hpp"
#include "ui/elements/ProgressBar.hpp"

class VolumeState : public SettingState
{
private:
    int volumeLevel;
    constexpr static int DEFAULT_VOLUME = 15; // Default volume level
    constexpr static int ROTATION_STEP = 1;   // Step size for volume adjustment
    constexpr static int MIN_VOLUME = 0;      // Minimum volume level
    constexpr static int MAX_VOLUME = 30;     // Maximum volume level

    UIElement *defaultUI;
    UIElement *menuUI;
    ProgressBar *progressBar;

    void publishVolumeEvent()
    {
        Event volumeEvent(EventType::VOLUME_CHANGED, DataType::INT);
        volumeEvent.intData.value = volumeLevel;
        EventBus::getInstance().publish(volumeEvent);
    }

public:
    VolumeState();

    void handleRotation(int delta) override;
    void handleButtonPress() override;
    void update() override;
    void updateDisplay(IDisplay *display) override;
    UIElement *getDefaultUI() override;
    UIElement *getMenuUI() override;
    void resetState() override;

    // Static members for the volume icon
    static const uint8_t icon_volume[];
    static const int ICON_VOLUME_WIDTH = 32;
    static const int ICON_VOLUME_HEIGHT = 32;
};
