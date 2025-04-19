#pragma once

#include "states/SettingState.hpp"

class BrightnessState : public SettingsState {
private:
    float brightnessLevel;

public:
    BrightnessState();
    void handleRotation(int delta) override;
    void handleButtonPress() override;
    void updateDisplay(OLEDDisplay* display) override;
};