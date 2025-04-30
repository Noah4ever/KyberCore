#pragma once

#include "core/SettingsStateMachine.hpp"
#include "core/DisplayManager.hpp"
#include "core/ComponentFactory.hpp"

#include "components/IComponent.hpp"
#include "components/audio/IAudioPlayer.hpp"
#include "components/sdcard/SDCardIO.hpp"

#include "events/EventBus.hpp"
#include "events/EventType.hpp"
#include "events/IEventListener.hpp"

#include "states/BrightnessState.hpp"
#include "states/ColorState.hpp"
#include "states/VolumeState.hpp"

#include <Arduino.h>
#include <ArduinoJson.h>
#include <map>

class LightsaberController : public IEventListener {
private:
    bool bladeIsIgnited = false;

    SDCardIO* sdCardIO = nullptr;
    IAudioPlayer* audioPlayer = nullptr;

    std::map<const char*, IComponent*> components;
    SettingsStateMachine* settingsStateMachine = nullptr;
    DisplayManager* displayManager = nullptr;

    void handleGenericButtonPressed(const Event& event);
    void handleGenericButtonReleased(const Event& event);
    void handleGenericButtonClicked(const Event& event);
    void handleGenericButtonLongPressed(const Event& event);
    void handleGenericButtonDoubleClicked(const Event& event);

    void igniteBlade();
    void extinguishBlade();

public:
    LightsaberController(SDCardIO* sdCardIO, IAudioPlayer* audioPlayer);
    ~LightsaberController() override = default;

    void setup();
    void update();

    void handleEvent(const Event& event) override;
};