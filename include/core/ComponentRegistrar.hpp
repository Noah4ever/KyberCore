#pragma once

#include <components/ComponentType.hpp>
#include <core/ComponentRegistry.hpp>
#include <ArduinoJson.h>

template<ComponentType T>
class ComponentRegistrar {
public:
    ComponentRegistrar(const std::string& typeStr, ComponentRegistry::Creator creator) {
        ComponentRegistry::instance().registerCreator(T, typeStr, creator);
    }
};

