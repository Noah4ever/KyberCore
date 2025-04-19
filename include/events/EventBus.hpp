#pragma once

#include <map>
#include <vector>
#include <functional> // For std::function 

#include "events/EventType.hpp"

class IEventListener;

// Interface for event listeners
struct Event {
    Event(EventType type, DataType dataType) : type(type), dataType(dataType) {}
    ~Event() {}
    
    EventType type;
    DataType dataType;
    union {
        IntData intData;
        FloatData floatData;
        BoolData boolData;
        StringData stringData;
        VolumeData volumeData;
        ColorData colorData;
        Vector3D vector3DData;
        IMUData imuData;
        // Add more data types as needed
    };
};

class EventBus {
private:
    std::map<EventType, std::vector<IEventListener*>> listeners;
    static EventBus* instance;
    EventBus() {} // Private Constructor for Singleton
    ~EventBus() {} // Private Destructor

    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

public:
    static EventBus& getInstance();

    void subscribe(IEventListener* listener, EventType eventType);
    void unsubscribe(IEventListener* listener, EventType eventType);
    void publish(const Event& event);
};
