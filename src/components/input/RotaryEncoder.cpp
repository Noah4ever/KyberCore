#include "components/input/RotaryEncoder.hpp"
#include "core/ComponentRegistrar.hpp"
#include "events/EventBus.hpp"
#include "events/EventType.hpp"

RotaryEncoder::RotaryEncoder(const ArduinoJson::JsonObjectConst& config) 
    : clkPin(config["rotary_encoder"]["clkPin"] | 5)
    , dtPin(config["rotary_encoder"]["dtPin"] | 17)
    , swPin(config["rotary_encoder"]["swPin"] | 16) {

        pinMode(clkPin, INPUT_PULLUP); // Set CLK pin as input with pull-up
        pinMode(dtPin, INPUT_PULLUP);  // Set DT pin as input with pull-up
        pinMode(swPin, INPUT_PULLUP);  // Set SW pin as input with pull-up
}

void RotaryEncoder::setup() {
    lastCLKState = digitalRead(clkPin); // Read initial state of CLK pin
    lastButtonState = digitalRead(swPin); // Read initial state of button
}

void RotaryEncoder::update() {
    readEncoder();
    readButton();
}


void RotaryEncoder::readEncoder() {
    int currentCLKState = digitalRead(clkPin);
    int currentDTState = digitalRead(dtPin);

    if (currentCLKState != lastCLKState && (millis() - lastRotaryTime) > ROTARY_DEBOUNCE_MS) {

        Event rotaryEvent(EventType::ROTARY_ROTATION_CHANGED, DataType::INT);

        if (currentDTState != currentCLKState) {
            encoderPos = 1;
        } else {
            encoderPos = -1;
        }

        rotaryEvent.intData.value = encoderPos;
        EventBus::getInstance().publish(rotaryEvent);

        lastRotaryTime = millis();
    }
    lastCLKState = currentCLKState;
}


void RotaryEncoder::readButton() {
    bool cur = digitalRead(swPin);
    unsigned long now = millis();

    // State change & debounce
    if (cur != lastButtonState && (now - lastButtonTime) >= BUTTON_DEBOUNCE_MS) {
        lastButtonTime = now;

        if (cur == LOW) {
            // Button down
            pressTime = now;
            EventBus::getInstance().publish(
              Event{EventType::ROTARY_BUTTON_PRESSED, DataType::NONE}
            );
        } 
        else {
            // Button up
            unsigned long held = now - pressTime;
            auto& bus = EventBus::getInstance();

            // Long‑press
            if (held >= LONG_PRESS_MS) {
                bus.publish(Event{EventType::ROTARY_BUTTON_LONG_PRESSED, DataType::NONE});
                Serial.println("Button Long Pressed");
            } 
            else {
                // Click: track for double‑click
                clickCount++;
                if (clickCount == 1) {
                    lastReleaseTime = now;
                } 
                else if (clickCount == 2 && (now - lastReleaseTime) <= DOUBLE_CLICK_MS) {
                    bus.publish(Event{EventType::ROTARY_BUTTON_DOUBLE_CLICKED, DataType::NONE});
                    clickCount = 0;  // reset
                    Serial.println("Button Double Clicked");
                }
            }

            // Always publish RELEASED
            bus.publish(Event{EventType::ROTARY_BUTTON_RELEASED, DataType::NONE});
        }
    }

    // Single‑click timeout
    if (clickCount == 1 && (now - lastReleaseTime) > DOUBLE_CLICK_MS) {
        Serial.println("Button Clicked");
        EventBus::getInstance().publish(
          Event{EventType::ROTARY_BUTTON_CLICKED, DataType::NONE}
        );
        clickCount = 0;
    }

    lastButtonState = cur;
}

static ComponentRegistrar<ComponentType::ROTARY_ENCODER_GENERIC> registrar("generic",
    [] (const ArduinoJson::JsonObjectConst& config) -> IComponent* {
        return new RotaryEncoder(config);
    }
);