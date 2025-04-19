#pragma once

#include <components/ComponentType.hpp>
#include <ArduinoJson.h>

template<ComponentType T>
class ComponentRegistrar {
public:
    ComponentRegistrar(
        std::function<IComponent*(const ArduinoJson::JsonObjectConst&)>
        creator
    ) {
        ComponentRegistry::instance().registerCreator(T, creator);
    }
};
