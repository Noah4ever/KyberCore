#pragma once

#include "components/display/IDisplay.hpp"
#include "events/IEventListener.hpp"
#include "SettingsStateMachine.hpp"

class DisplayManager : public IEventListener {
    public:
        DisplayManager();
        ~DisplayManager();

        void setup();
        void update();

        void setDisplay(IDisplay* display);
        void setSettingsStateMachine(SettingsStateMachine* settingsStateMachine);
        void handleEvent(const Event& event) override;

    private:
        IDisplay* display;
        SettingsStateMachine* settingsStateMachine;
        SettingState* currentState;
};