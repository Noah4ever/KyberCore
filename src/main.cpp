#include "Arduino.h"

#include <Wire.h>
#include <map>

#include "core/ComponentFactory.hpp"
#include "components/ComponentType.hpp"

#include "core/SettingsStateMachine.hpp"
#include "states/BrightnessState.hpp"
#include "states/VolumeState.hpp"

std::map<ComponentType, IComponent*> components;

SettingsStateMachine* settingsStateMachine = new SettingsStateMachine();

void setup()
{
  Serial.begin(115200);

  ComponentFactory factory;

  // Could be read from a config file or JSON
  ComponentType componentTypes[] = {
    ComponentType::IMU_MPU6500,
  };

  
  for (auto type : componentTypes) {
    components[type] = factory.create(type, ArduinoJson::JsonObjectConst());

    if (components[type] != nullptr) {
      components[type]->setup();
    } else {
      Serial.println("Failed to create component");
    }
  }

  // Setup the settings state machine
  settingsStateMachine->setup();
  settingsStateMachine->addState(new BrightnessState());
  settingsStateMachine->addState(new VolumeState());



}

void loop()
{
  Serial.println("Main loop running...");
  
  // Update all components
  for (auto& component : components) {
    if (component.second != nullptr) {
      component.second->update();
    }
  }

  delay(200); // Adjust the delay as needed
}
