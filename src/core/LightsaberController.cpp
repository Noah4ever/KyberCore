#include "core/LightsaberController.hpp"

LightsaberController::LightsaberController(SDCardIO *sdCardIO, IAudioPlayer *audioPlayer)
{
    this->sdCardIO = sdCardIO;
    this->audioPlayer = audioPlayer;
    this->settingsStateMachine = new SettingsStateMachine();
    this->displayManager = new DisplayManager();
}

void LightsaberController::setup()
{
    ComponentFactory factory;

    if (sdCardIO == nullptr)
    {
        while (1)
        {
            Serial.println("SDCardIO is null!");
            delay(1000);
        }
    }

#if 1
    const char *configJson = R"(
        {
          "blade": { "type": "neopixel", "numLeds": 120, "brightness": 80 },
          "imu": { "type": "mpu6500", "i2c_sda": 21, "i2c_scl": 22, "interrupt_pin": 34 }    ,
          "rotary_encoder": { "type": "rotary_encoder_generic", "clkPin": 5, "dtPin": 17, "swPin": 16 },
          "display": { "type": "ssd1306" },
          "button": { "type": "button_generic", "pin": 4, "mode": "INPUT_PULLUP" }
        }
        )";
#else
    // read config.json from sd card
    const char *configJson = sdCardIO->readConfigFile("config.json").c_str();

    if (configJson == nullptr)
    {
        while (1)
        {
            Serial.println("Failed to read config file (config.json)!");
            delay(1000);
        }
    }
#endif
    JsonDocument configDoc;

    auto error = deserializeJson(configDoc, configJson);
    if (error)
    {
        while (1)
        {
            Serial.println("JSON parse failed!");
            delay(1000);
        }
    }

    JsonObject root = configDoc.as<JsonObject>();

    for (const auto &key : {"blade", "imu", "rotary_encoder", "display", "sound_controller", "button"})
    {
        if (root[key].isNull())
            continue;

        auto config = root[key].as<ArduinoJson::JsonObjectConst>();
        const char *typeStr = config["type"];
        if (!typeStr || typeStr == "")
            continue;

        IComponent *comp = factory.create(typeStr, config);
        if (comp)
        {
            components[key] = comp;

            comp->setup();
        }
        else
        {
            Serial.printf("Failed to create component for key: %s\n", key);
        }
    }

    settingsStateMachine->addState(new BrightnessState());
    settingsStateMachine->addState(new ColorState());
    settingsStateMachine->addState(new VolumeState());

    displayManager->setSettingsStateMachine(settingsStateMachine);
    if (components["display"])
    {
        displayManager->setDisplay(static_cast<IDisplay *>(components["display"]));
        displayManager->setup();
    }

    // Has to be called after displayManager->setup() to let the
    // displayManager to subcribe to the event "STATE_CHANGED" so initial state
    // can be displayed
    settingsStateMachine->setup();

    audioPlayer->setup();
    audioPlayer->play("/font1/font.wav");

    EventBus::getInstance().subscribe(this, EventType::GENERIC_PUSH_BUTTON_PRESSED);
    EventBus::getInstance().subscribe(this, EventType::GENERIC_PUSH_BUTTON_RELEASED);
    EventBus::getInstance().subscribe(this, EventType::GENERIC_PUSH_BUTTON_CLICKED);
    EventBus::getInstance().subscribe(this, EventType::GENERIC_PUSH_BUTTON_LONG_PRESSED);
    EventBus::getInstance().subscribe(this, EventType::GENERIC_PUSH_BUTTON_DOUBLE_CLICKED);

    // Add imu subscribe, so sound can play
}

void LightsaberController::update()
{
    // Periodically update each component (poll sensors, handle inputs, etc.)
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        IComponent *comp = it->second;
        if (comp)
        {
            comp->update();
        }
    }

    settingsStateMachine->getCurrentState()->update();

    audioPlayer->update();
    // No need to read the button directly here, events will trigger actions
}

void LightsaberController::handleEvent(const Event &event)
{
    switch (event.type)
    {
    case EventType::GENERIC_PUSH_BUTTON_PRESSED:
        handleGenericButtonPressed(event);
        break;
    case EventType::GENERIC_PUSH_BUTTON_RELEASED:
        handleGenericButtonReleased(event);
        break;
    case EventType::GENERIC_PUSH_BUTTON_CLICKED:
        handleGenericButtonClicked(event);
        break;
    case EventType::GENERIC_PUSH_BUTTON_LONG_PRESSED:
        handleGenericButtonLongPressed(event);
        break;
    case EventType::GENERIC_PUSH_BUTTON_DOUBLE_CLICKED:
        handleGenericButtonDoubleClicked(event);
        break;
    default:
        break;
    }
}

void LightsaberController::handleGenericButtonPressed(const Event &event)
{
    // You might want to track the press for specific sequences later
}

void LightsaberController::handleGenericButtonReleased(const Event &event)
{
    // You might want to track the release for specific sequences later
}

void LightsaberController::handleGenericButtonClicked(const Event &event)
{
    if (!bladeIsIgnited)
    {
        igniteBlade();
    }
    else
    {
        extinguishBlade();
    }
}

void LightsaberController::handleGenericButtonLongPressed(const Event &event)
{
    // Potentially trigger a different action with a long press
}

void LightsaberController::handleGenericButtonDoubleClicked(const Event &event)
{
    // Potentially trigger another action with a double click
}

void LightsaberController::igniteBlade()
{
    bladeIsIgnited = true;
    Event igniteEvent(EventType::BLADE_IGNITE, DataType::NONE);
    EventBus::getInstance().publish(igniteEvent);
    // Trigger other ignition effects
}

void LightsaberController::extinguishBlade()
{
    bladeIsIgnited = false;
    Event extinguishEvent(EventType::BLADE_EXTINGUISH, DataType::NONE);
    EventBus::getInstance().publish(extinguishEvent);
    // Trigger other extinguishing effects
}
