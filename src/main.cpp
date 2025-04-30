#include "Arduino.h"

#include "core/LightsaberController.hpp"
#include "components/sdcard/ESP32SDCardIO.hpp"
#include "components/audio/ESP32SDCardAudioPlayer.hpp"

/*
  TODO: Implement a UI Builder to create the UI in the States to emit the created object to the display
  TODO: Implement all settings get a setup call to publish the initial state
  TODO: Implement Blaster Reflect, Blade Lock, and other blade effects
  TODO: Implement a state machine for the blade to handle the blade effects ?? Maybe. was created by github copilot
  TODO: Implement more colors. not only rgb but also animation of the colors and variations of the colors like unstable
  TODO: Create menu state with submenu, scroll lists, etc. padding, container direction: vertical/horizontal.
    When in the menu use the rotary encoder to scroll through the menu items and select them with the button.
*/

// Main controller for lightsaber functionality
LightsaberController *lightsaberController;

void setup()
{
  Serial.begin(115200);

  // Initialize SDCard IO
  ESP32SDCardIO* sdCardIO = new ESP32SDCardIO(27);
  if (!sdCardIO->initializeSD()) {
      while (1) {
          Serial.println("Failed to initialize SD card!");
          delay(1000);
      }
  }
  // Initialize Audio Player
  ESP32SDCardAudioPlayer* audioPlayer = new ESP32SDCardAudioPlayer(sdCardIO);

  // Initialize Lightsaber Controller
  lightsaberController = new LightsaberController(sdCardIO, audioPlayer);
  lightsaberController->setup();
}

void loop()
{
  // Update the lightsaber controller
  lightsaberController->update();
  // Short delay
  delay(1);
}
