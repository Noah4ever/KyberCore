
#include "states/VolumeState.hpp"
#include "events/EventBus.hpp"
#include "events/EventType.hpp"
#include "Arduino.h" // For Serial print
#include <cmath> 

VolumeState::VolumeState() : volumeLevel(DEFAULT_VOLUME) {}

void VolumeState::handleRotation(int delta) {
    volumeLevel += delta * ROTATION_STEP;
    volumeLevel = std::fmax(MIN_VOLUME, std::fmin(MAX_VOLUME, volumeLevel));

    Event volumeEvent(EventType::VOLUME_CHANGED, DataType::INT);
    volumeEvent.intData.value = volumeLevel;
    EventBus::getInstance().publish(volumeEvent);

    Event igniteEvent(EventType::BLADE_IGNITE, DataType::JSON_OBJECT);
    igniteEvent.jsonData = ArduinoJson::JsonObject();
    EventBus::getInstance().publish(igniteEvent);

    Serial.print("Volume Level: ");
    Serial.println(volumeLevel);
    
}

void VolumeState::handleButtonPress() {
    
}

void VolumeState::update() {
    // Update logic if needed
}

void VolumeState::updateDisplay(IDisplay* display) {
    if (display) {
        display->clear();
        display->drawString(0, 0, "Volume");
        // display->drawProgressBar(0, 10, 128, 8, static_cast<int>(volumeLevel * 100));
        display->display();
    }
}

void VolumeState::resetState() {
    volumeLevel = DEFAULT_VOLUME; // Reset to default value
}