#include "Arduino.h"

#include <Wire.h>
#include <map>

#include "core/ComponentFactory.hpp"
#include "components/ComponentType.hpp"


std::map<ComponentType, IComponent*> components;


void setup()
{
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
}

void loop()
{
  
  // Update all components
  for (auto& component : components) {
    if (component.second != nullptr) {
      component.second->update();
    }
  }

  delay(20); // Adjust the delay as needed
}
