#include "Arduino.h"
#include <Wire.h>
#include <map>
#include <ArduinoJson.h>

#include "core/ComponentFactory.hpp"
#include "components/ComponentType.hpp"

#include "core/SettingsStateMachine.hpp"
#include "states/BrightnessState.hpp"
#include "states/ColorState.hpp"
#include "states/VolumeState.hpp"

// Store components by type for setup and periodic updates
std::map<const char*, IComponent *> components;

// Manage UI states (e.g., adjusting brightness/volume)
SettingsStateMachine *settingsStateMachine = new SettingsStateMachine();

// JSON config: defines hardware setup for blade, IMU, encoder, etc.
const char *configJson = R"(
{
  "blade": { "type": "neopixel", "numLeds": 120, "brightness": 80 },
  "imu": { "type": "mpu6500", "i2c_sda": 21, "i2c_scl": 22, "interrupt_pin": 34 },
  "rotary_encoder": { "type": "generic", "clkPin": 5, "dtPin": 17, "swPin": 16 },
  "display": { "type": "ssd1306" },
  "sound_controller": { "type": "dfplayer_mini" }
}
)";

void setup()
{
  Serial.begin(115200);

  ComponentFactory factory;

  // Parse JSON; on failure, log error and skip component setup
  JsonDocument configDoc;

  auto error = deserializeJson(configDoc, configJson);
  if (error)
  {
    Serial.printf("JSON parse failed: %s\n", error.c_str());
    return;
  }
  JsonObject root = configDoc.as<JsonObject>();

  for (const auto& key : {"blade", "imu", "rotary_encoder", "display", "sound_controller"}) {
    if (root[key].isNull()) continue;

    auto config = root[key].as<ArduinoJson::JsonObjectConst>();
    const char* typeStr = config["type"];
    if (!typeStr || typeStr == "") continue;

    IComponent* comp = factory.create(typeStr, config);
    if (comp) {
        components[key] = comp;

        comp->setup();
    } else {
        Serial.printf("Failed to create component for key: %s\n", key);
    }
}

  // Initialize UI state machine with screens for brightness and volume
  settingsStateMachine->setup();
  settingsStateMachine->addState(new BrightnessState());
  settingsStateMachine->addState(new ColorState());
  settingsStateMachine->addState(new VolumeState());
}


/*
1.  FIX: implementation of DFPlayer Mini
2.  TODO: Implement a UI Builder to create the UI in the States to emit the created object to the display
3.  TODO: Implement all settings get a setup call to publish the initial state
4.  TODO: Implement Blaster Reflect, Blade Lock, and other blade effects
5.  TODO: Implement a state machine for the blade to handle the blade effects ?? Maybe. was created by github copilot
6.  TODO: Implement more colors. not only rgb but also animation of the colors and variations of the colors like unstable
4.  TODO: Create menu state with submenu, scroll lists, etc. padding, container direction: vertical/horizontal. 
  When in the menu use the rotary encoder to scroll through the menu items and select them with the button.
*/
void loop()
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

  delay(2); // Short pause to yield CPU to other tasks/peripherals
}