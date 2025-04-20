#include "Arduino.h"
#include <Wire.h>
#include <map>
#include <ArduinoJson.h>

#include "core/ComponentFactory.hpp"
#include "components/ComponentType.hpp"

#include "core/SettingsStateMachine.hpp"
#include "states/BrightnessState.hpp"
#include "states/VolumeState.hpp"

// Store components by type for setup and periodic updates
std::map<const char*, IComponent *> components;

// Manage UI states (e.g., adjusting brightness/volume)
SettingsStateMachine *settingsStateMachine = new SettingsStateMachine();

// JSON config: defines hardware setup for blade, IMU, encoder, etc.
const char *configJson = R"(
{
  "blade": { "type": "neopixel", "numLeds": 120, "brightness": 80 },
  "imu": { "type": "mpu6500", "address": 68, "sda_pin": 21, "scl_pin": 22, "interrupt_pin": 34 },
  "rotary_encoder": { "type": "generic", "clkPin": 5, "dtPin": 17, "swPin": 16 },
  "display": { "type": "" },
  "sound_controller": { "type": "" }
}
)";

void setup()
{
  Serial.begin(115200);

  ComponentFactory factory;

  // Parse JSON; on failure, log error and skip component setup
  JsonDocument configDoc;
  delay(5000); // Allow time for Serial to initialize
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
  settingsStateMachine->addState(new VolumeState());
}

void loop()
{
  Serial.println("Main loop running...");
  Serial.print("components.size() = "); 
  Serial.println(components.size());
  

  // Periodically update each component (poll sensors, handle inputs, etc.)
  for (auto it = components.begin(); it != components.end(); ++it)
  {
    IComponent *comp = it->second;
    if (comp)
    {
      comp->update();
    }
  }

  delay(2); // Short pause to yield CPU to other tasks/peripherals
}