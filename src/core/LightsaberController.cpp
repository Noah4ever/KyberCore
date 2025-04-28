#include "core/LightsaberController.hpp"
#include "core/ComponentRegistrar.hpp"
#include "events/EventBus.hpp"
#include "events/EventType.hpp"

LightsaberController::LightsaberController(const ArduinoJson::JsonObjectConst& config) {
    // No need to read a specific pin here, we're subscribing to generic button events
}

LightsaberController::LightsaberController() {
    // No need to read a specific pin here, we're subscribing to generic button events
}

void LightsaberController::setup() {
    EventBus::getInstance().subscribe(this, EventType::GENERIC_BUTTON_PRESSED);
    EventBus::getInstance().subscribe(this, EventType::GENERIC_BUTTON_RELEASED);
    EventBus::getInstance().subscribe(this, EventType::GENERIC_BUTTON_CLICKED);
    EventBus::getInstance().subscribe(this, EventType::GENERIC_BUTTON_LONG_PRESSED);
    EventBus::getInstance().subscribe(this, EventType::GENERIC_BUTTON_DOUBLE_CLICKED);

    // Add imu subscribe, so sound can play

}

void LightsaberController::update() {
    // No need to read the button directly here, events will trigger actions
}

void LightsaberController::handleEvent(const Event& event) {
    switch (event.type) {
        case EventType::GENERIC_BUTTON_PRESSED:
            handleGenericButtonPressed(event);
            break;
        case EventType::GENERIC_BUTTON_RELEASED:
            handleGenericButtonReleased(event);
            break;
        case EventType::GENERIC_BUTTON_CLICKED:
            handleGenericButtonClicked(event);
            break;
        case EventType::GENERIC_BUTTON_LONG_PRESSED:
            handleGenericButtonLongPressed(event);
            break;
        case EventType::GENERIC_BUTTON_DOUBLE_CLICKED:
            handleGenericButtonDoubleClicked(event);
            break;
        default:
            break;
    }
}

void LightsaberController::handleGenericButtonPressed(const Event& event) {
    // You might want to track the press for specific sequences later
}

void LightsaberController::handleGenericButtonReleased(const Event& event) {
    // You might want to track the release for specific sequences later
}

void LightsaberController::handleGenericButtonClicked(const Event& event) {
    if (!bladeIsIgnited) {
        igniteBlade();
    } else {
        extinguishBlade();
    }
}

void LightsaberController::handleGenericButtonLongPressed(const Event& event) {
    // Potentially trigger a different action with a long press
}

void LightsaberController::handleGenericButtonDoubleClicked(const Event& event) {
    // Potentially trigger another action with a double click
}

void LightsaberController::igniteBlade() {
    bladeIsIgnited = true;
    Event igniteEvent(EventType::BLADE_IGNITE, DataType::NONE);
    EventBus::getInstance().publish(igniteEvent);
    // Trigger other ignition effects
}

void LightsaberController::extinguishBlade() {
    bladeIsIgnited = false;
    Event extinguishEvent(EventType::BLADE_EXTINGUISH, DataType::NONE);
    EventBus::getInstance().publish(extinguishEvent);
    // Trigger other extinguishing effects
}
