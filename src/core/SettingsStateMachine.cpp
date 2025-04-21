#include "core/SettingsStateMachine.hpp"
#include "states/SettingState.hpp"
#include "events/EventBus.hpp"
#include "components/display/Display.hpp" 

#include "Arduino.h" // Serial print

SettingsStateMachine::SettingsStateMachine() : currentStateIndex(0) {}

SettingsStateMachine::~SettingsStateMachine() {
    for (SettingState* state : states) {
        delete state;
    }
    states.clear();
}

void SettingsStateMachine::setup() {
    EventBus::getInstance().subscribe(this, EventType::ROTARY_BUTTON_CLICKED);
    EventBus::getInstance().subscribe(this, EventType::ROTARY_ROTATION_CHANGED);
}

void SettingsStateMachine::addState(SettingState* state) {
    states.push_back(state);
}

void SettingsStateMachine::handleRotation(int delta) {
    if (!states.empty() && currentStateIndex >= 0 && currentStateIndex < states.size() && states[currentStateIndex]) {
        states[currentStateIndex]->handleRotation(delta);
    }
}

void SettingsStateMachine::handleButtonPress() {
    if (!states.empty()) {
        currentStateIndex = (currentStateIndex + 1) % states.size();
        Serial.print("Switching to state: ");
        Serial.println(currentStateIndex);
    }
}

SettingState* SettingsStateMachine::getCurrentState() const {
    if (!states.empty() && currentStateIndex >= 0 && currentStateIndex < states.size()) {
        return states[currentStateIndex];
    }
    return nullptr; // Or handle error as needed
}

void SettingsStateMachine::handleEvent(const Event& event) {
    switch (event.type) {
        case EventType::ROTARY_ROTATION_CHANGED:
            if(event.dataType == DataType::INT) {
                int delta = event.intData.value;
                handleRotation(delta);
            }
            break;
        case EventType::ROTARY_BUTTON_CLICKED:
            handleButtonPress();
        default:
            break;
    }
}