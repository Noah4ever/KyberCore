
#pragma once


#include "components/ComponentType.hpp"
#include "components/IComponent.hpp"
#include "ComponentRegistry.hpp"

#include <ArduinoJson.h>

class ComponentFactory {
    public:
        virtual IComponent* create(ComponentType type,
            const ArduinoJson::JsonObjectConst& config) {
            return ComponentRegistry::instance().create(type, config);
        }
    
};