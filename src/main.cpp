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

// Main controller for lightsaber functionality (blade ignition, sound, etc.)
LightsaberController *lightsaberController;

// JSON config: defines hardware setup for blade, IMU, encoder, etc.


void setup()
{
  Serial.begin(115200);

  ESP32SDCardIO* sdCardIO = new ESP32SDCardIO(27);
  if (!sdCardIO->initializeSD()) {
      while (1) {
          Serial.println("Failed to initialize SD card!");
          delay(1000);
      }
  }
  
  ESP32SDCardAudioPlayer* audioPlayer = new ESP32SDCardAudioPlayer(sdCardIO);

  lightsaberController = new LightsaberController(sdCardIO, audioPlayer);
  lightsaberController->setup();

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
  lightsaberController->update();

  delay(1); // Short pause to yield CPU to other tasks/peripherals
}
