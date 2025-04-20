
#pragma once


#include "components/ComponentType.hpp"
#include "components/IComponent.hpp"
#include "ComponentRegistry.hpp"

#include <ArduinoJson.h>

class ComponentFactory {
    public:
        IComponent* create(const std::string& typeStr, const ArduinoJson::JsonObjectConst& config) {
            ComponentType type = ComponentRegistry::instance().getComponentType(typeStr);
            if (type == ComponentType::UNKNOWN) {
                return nullptr;
            }
            return ComponentRegistry::instance().create(type, config);
        }
    };
    