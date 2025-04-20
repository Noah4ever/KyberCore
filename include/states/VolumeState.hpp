#pragma once

#include "states/SettingState.hpp"
#include "components/display/Display.hpp"

class VolumeState : public SettingState {
private:
    int volumeLevel;
    constexpr static int DEFAULT_VOLUME = 15; // Default volume level
    constexpr static int ROTATION_STEP = 1; // Step size for volume adjustment
    constexpr static int MIN_VOLUME = 0; // Minimum volume level
    constexpr static int MAX_VOLUME = 30; // Maximum volume level

public:
    VolumeState();

    void handleRotation(int delta) override;
    void handleButtonPress() override;
    void updateDisplay(IDisplay* display) override;
    void resetState() override;
};

