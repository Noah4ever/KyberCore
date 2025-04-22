#pragma once

#include "components/display/IDisplay.hpp"

class SettingState{
public: 
    virtual ~SettingState() = default;
    /**
     * @brief Handles the rotation of the setting.
     *
     * @param delta The amount of rotation (positive or negative).
     */
    virtual void handleRotation(int delta) = 0;

    /**
     * @brief Handles the button press.
     */
    virtual void handleButtonPress() = 0;

    /**
     * @brief Lets a settings state update itself when its selected.
     */
    virtual void update() = 0;

    /**
     * @brief Updates the display with the current state information.
     *
     */
    virtual void updateDisplayData() = 0;

    /**
     * @brief Resets the state of the setting.
     */
    virtual void resetState() = 0;
};