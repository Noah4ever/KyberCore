#pragma once

#include "states/SettingState.hpp"
#include "events/IEventListener.hpp"

#include <map>

// TOOD: Enter secret mode with a specific button press and rotation pattern
class SettingsStateMachine : public IEventListener 
{
private:
    int currentStateIndex;
    std::vector<SettingState*> states;
    
public:
    SettingsStateMachine();
    ~SettingsStateMachine();

    void setup();

    void handleRotation(int delta);
    void handleButtonPress();

    void addState(SettingState* state);
    SettingState* getCurrentState() const;

    void handleEvent(const Event& event) override;

};