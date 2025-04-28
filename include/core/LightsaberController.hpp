#pragma once

#include "components/IComponent.hpp"
#include "events/EventBus.hpp"
#include "events/EventType.hpp"
#include "events/IEventListener.hpp"


#include <Arduino.h>
#include <ArduinoJson.h>

class LightsaberController : public IEventListener {
private:
    bool bladeIsIgnited = false;

    void handleGenericButtonPressed(const Event& event);
    void handleGenericButtonReleased(const Event& event);
    void handleGenericButtonClicked(const Event& event);
    void handleGenericButtonLongPressed(const Event& event);
    void handleGenericButtonDoubleClicked(const Event& event);

    void igniteBlade();
    void extinguishBlade();

public:
    LightsaberController(const ArduinoJson::JsonObjectConst& config);
    LightsaberController();
    ~LightsaberController() override = default;

    void setup();
    void update();

    void handleEvent(const Event& event) override;
};