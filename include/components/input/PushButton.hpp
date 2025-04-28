#pragma once

#include "components/IComponent.hpp"
#include "events/EventBus.hpp"
#include "events/EventType.hpp"

#include <Arduino.h> // For digitalRead, pinMode
#include <ArduinoJson.h> // For ArduinoJson::JsonObjectConst

class PushButton : public IComponent {
private:
    uint8_t buttonPin;

    const unsigned long BUTTON_DEBOUNCE_MS = 50;
    unsigned long lastButtonTime = 0;
    bool lastButtonState = HIGH; // Assuming button is normally open with pull-up

    unsigned long pressTime = 0;    // when button went LOW
    unsigned long lastReleaseTime = 0;    // when button went HIGH
    uint8_t clickCount = 0;    // number of releases within window

    static constexpr unsigned long LONG_PRESS_MS = 800;  // hold threshold
    static constexpr unsigned long DOUBLE_CLICK_MS = 200;  // max gap

public:
    PushButton(const ArduinoJson::JsonObjectConst& config);
    ~PushButton() override = default;

    void setup() override;
    void update() override;

private:
    void readButton();
};