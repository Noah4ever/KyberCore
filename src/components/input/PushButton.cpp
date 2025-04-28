#include "components/input/PushButton.hpp"
#include "core/ComponentRegistrar.hpp"
#include "events/EventBus.hpp"
#include "events/EventType.hpp"

PushButton::PushButton(const ArduinoJson::JsonObjectConst& config)
    : buttonPin(config["push_button"]["pin"] | 4) {
    pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up
}

void PushButton::setup() {
    lastButtonState = digitalRead(buttonPin); // Read initial state of button
}

void PushButton::update() {
    readButton();
}

void PushButton::readButton() {
    bool cur = digitalRead(buttonPin);
    unsigned long now = millis();

    // State change & debounce
    if (cur != lastButtonState && (now - lastButtonTime) >= BUTTON_DEBOUNCE_MS) {
        lastButtonTime = now;

        if (cur == LOW) {
            // Button down
            pressTime = now;
            EventBus::getInstance().publish(
                Event{EventType::GENERIC_BUTTON_PRESSED, DataType::NONE}
            );
        } else {
            // Button up
            unsigned long held = now - pressTime;
            auto& bus = EventBus::getInstance();

            // Long-press
            if (held >= LONG_PRESS_MS) {
                bus.publish(Event{EventType::GENERIC_BUTTON_LONG_PRESSED, DataType::NONE});
                Serial.println("Button Long Pressed");
            } else {
                // Click: track for double-click
                clickCount++;
                if (clickCount == 1) {
                    lastReleaseTime = now;
                } else if (clickCount == 2 && (now - lastReleaseTime) <= DOUBLE_CLICK_MS) {
                    bus.publish(Event{EventType::GENERIC_BUTTON_DOUBLE_CLICKED, DataType::NONE});
                    clickCount = 0;  // reset
                    Serial.println("Button Double Clicked");
                }
            }

            // Always publish RELEASED
            bus.publish(Event{EventType::GENERIC_BUTTON_RELEASED, DataType::NONE});
        }
    }

    // Single-click timeout
    if (clickCount == 1 && (now - lastReleaseTime) > DOUBLE_CLICK_MS) {
        Serial.println("Button Clicked");
        EventBus::getInstance().publish(
            Event{EventType::GENERIC_BUTTON_CLICKED, DataType::NONE}
        );
        clickCount = 0;
    }

    lastButtonState = cur;
}

static ComponentRegistrar<ComponentType::PUSH_BUTTON_GENERIC> registrar("button_generic",
    [] (const ArduinoJson::JsonObjectConst& config) -> IComponent* {
        return new PushButton(config);
    }
);