#pragma once

#include <map>

// TOOD: Enter secret mode with a specific button press and rotation pattern
class SettingStateMachine
{
private:
    int currentState;
    std::map<StateType, int> settings;
    
public:
    SettingStateMachine();
    ~SettingStateMachine();

    void setup();
    void handleRotation(int delta);
    void handleButtonPress();

};