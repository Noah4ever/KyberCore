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
    void registerCreator(ComponentType type, const std::string& typeStr, Creator creator) {
        creators_[type] = creator;
        typeStringToEnum_[typeStr] = type;
    }

    // Get component type from string
    ComponentType getComponentType(const std::string& typeStr) const {
        auto it = typeStringToEnum_.find(typeStr);
        if (it != typeStringToEnum_.end()) {
            return it->second;
        }
        return ComponentType::UNKNOWN; 
    }
    

    // Create component instance using registered creator
    IComponent* create(ComponentType type, const ArduinoJson::JsonObjectConst& config) {
        if(creators_.count(type)) return creators_[type](config); // Execute creator lambda
        return nullptr; // Type not registered
    }

private:
    std::unordered_map<ComponentType, Creator> creators_;
    std::unordered_map<std::string, ComponentType> typeStringToEnum_;

    ComponentRegistry() = default; // Prevent direct instantiation
};