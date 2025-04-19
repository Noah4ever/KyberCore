#pragma once

#include "components/ComponentType.hpp" // Contains ComponentType enum
#include "components/IComponent.hpp" // Base class for components

#include <functional>
#include <unordered_map>
#include <ArduinoJson.h>

// Central storage for component creation functions
class ComponentRegistry {
public:
    using Creator = std::function<IComponent*(const ArduinoJson::JsonObjectConst&)>;
    
    // Singleton access - ensures single instance globally
    static ComponentRegistry& instance() {
        static ComponentRegistry registry;
        return registry;
    }

    // Register a creation function for a specific component type
    void registerCreator(ComponentType type, Creator creator) {
        creators_[type] = creator; // Store in hash map
    }

    // Create component instance using registered creator
    IComponent* create(ComponentType type, const ArduinoJson::JsonObjectConst& config) {
        if(creators_.count(type)) return creators_[type](config); // Execute creator lambda
        return nullptr; // Type not registered
    }

private:
    std::unordered_map<ComponentType, Creator> creators_;
    ComponentRegistry() = default; // Prevent direct instantiation
};