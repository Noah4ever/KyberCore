#pragma once

#include "components/IComponent.hpp"
#include "events/EventBus.hpp"
#include "events/EventType.hpp"

#include <Arduino.h> // For digitalRead, pinMode
#include <ArduinoJson.h> // For ArduinoJson::JsonObjectConst

class RotaryEncoder : public IComponent {
private:
    uint8_t clkPin, dtPin, swPin;

    const unsigned long ROTARY_DEBOUNCE_MS = 100;
    unsigned long lastRotaryTime = 0;
    int encoderPos = 0;
    int lastCLKState = LOW;
    bool lastButtonState = HIGH; // Assuming button is normally open with pull-up
    unsigned long lastButtonTime;
    static constexpr unsigned long BUTTON_DEBOUNCE_MS = 50;
  
    unsigned long   pressTime       = 0;    // when button went LOW
    unsigned long   lastReleaseTime = 0;    // when button went HIGH
    uint8_t         clickCount      = 0;    // number of releases within window
  
    static constexpr unsigned long LONG_PRESS_MS   = 700;  // hold threshold
    static constexpr unsigned long DOUBLE_CLICK_MS = 300;  // max gap

public:
    RotaryEncoder(const ArduinoJson::JsonObjectConst& config);
    ~RotaryEncoder() override = default;

    void setup() override;
    void update() override;

private:
    void readEncoder();
    void readButton();
};
