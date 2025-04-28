#include "Arduino.h"
#include <Wire.h>
#include <map>
#include <ArduinoJson.h>

#include "core/LightsaberController.hpp"

#include "core/DisplayManager.hpp"

#include "core/ComponentFactory.hpp"
#include "components/ComponentType.hpp"

#include "core/SettingsStateMachine.hpp"
#include "states/BrightnessState.hpp"
#include "states/ColorState.hpp"
#include "states/VolumeState.hpp"
#include <components/sdcard/ESP32SDCardIO.hpp>
#include <components/audio/ESP32SDCardAudioPlayer.hpp>

// Store components by type for setup and periodic updates
std::map<const char *, IComponent *> components;

// Manage UI states (e.g., adjusting brightness/volume)
SettingsStateMachine *settingsStateMachine = new SettingsStateMachine();

DisplayManager *displayManager = new DisplayManager();

// Main controller for lightsaber functionality (blade ignition, sound, etc.)
LightsaberController *lightsaberController = new LightsaberController();

// JSON config: defines hardware setup for blade, IMU, encoder, etc.
const char *configJson = R"(
{
  "blade": { "type": "neopixel", "numLeds": 120, "brightness": 80 },
  "imu": { "type": "mpu6500", "i2c_sda": 21, "i2c_scl": 22, "interrupt_pin": 34 },
  "rotary_encoder": { "type": "rotary_encoder_generic", "clkPin": 5, "dtPin": 17, "swPin": 16 },
  "display": { "type": "ssd1306" },
  "sound_controller": { "type": "" },
  "button": { "type": "button_generic", "pin": 4, "mode": "INPUT_PULLUP" }
}
)";

#define SD_CS_PIN 27
ESP32SDCardIO sdCardIO(SD_CS_PIN);
ESP32SDCardAudioPlayer audioPlayer(&sdCardIO);

void setup()
{
  Serial.begin(115200);

  if (!sdCardIO.initializeSD(SD_CS_PIN))
  {
    Serial.println("SD card initialization failed!");
    return;
  }

  ComponentFactory factory;

  // Parse JSON; on failure, log error and skip component setup
  JsonDocument configDoc;

  auto error = deserializeJson(configDoc, configJson);
  if (error)
  {
    Serial.printf("===========================================\nJSON parse failed: %s\n===========================================", error.c_str());
    while (1)
      delay(1000); // Wait indefinitely
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

  // Initialize UI state machine with screens for brightness and volume
  settingsStateMachine->addState(new BrightnessState());
  settingsStateMachine->addState(new ColorState());
  settingsStateMachine->addState(new VolumeState());

  // Initialize lightsaber controller
  lightsaberController->setup();

  // Initialize display manager
  displayManager->setSettingsStateMachine(settingsStateMachine);
  if (components["display"])
  {
    displayManager->setDisplay(static_cast<IDisplay *>(components["display"]));
  }
  displayManager->setup();

  // Initialize settings state machine
  settingsStateMachine->setup();

  // Initialize audio player
  audioPlayer.setup();

  // Start playing an audio file
  audioPlayer.play("/0001.mp3"); // Replace with the actual path to your MP3 file
}

/*
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

  audioPlayer.update();

  settingsStateMachine->getCurrentState()->update();

  delay(1); // Short pause to yield CPU to other tasks/peripherals
}