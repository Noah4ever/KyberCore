#pragma once

#include "components/display/IDisplay.hpp"
#include "ui/elements/UIElement.hpp"
#include "events/IEventListener.hpp"

class SettingState : public IEventListener
{
protected:
    bool bladeIsIgnited = false;

public:
    SettingState()
    {
        EventBus::getInstance().subscribe(this, EventType::BLADE_IGNITE);
        EventBus::getInstance().subscribe(this, EventType::BLADE_EXTINGUISH);
    }
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
     * @param display The display to update.
     */
    virtual void updateDisplay(IDisplay *display) = 0;

    /**
     * @brief Returns the default UI element for the setting.
     *
     * @return Pointer to the default UI element.
     */
    virtual UIElement *getDefaultUI() = 0;

    /**
     * @brief Returns the menu UI element for the setting.
     * 
     * @return Pointer to the menu UI element.
     */
    virtual UIElement *getMenuUI() = 0;

    /**
     * @brief Resets the state of the setting.
     */
    virtual void resetState() = 0;

    /**
     * @brief Handles the event.
     *
     * @param event The event to handle.
     */
    virtual void handleEvent(const Event &event)
    {
        if (event.type == EventType::BLADE_IGNITE)
        {
            bladeIsIgnited = true;
        }
        else if (event.type == EventType::BLADE_EXTINGUISH)
        {
            bladeIsIgnited = false;
        }
    }
};