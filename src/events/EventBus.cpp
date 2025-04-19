#include "events/EventBus.hpp"
#include "events/IEventListener.hpp" 

EventBus* EventBus::instance = nullptr;

EventBus& EventBus::getInstance() {
    if (!instance) {
        instance = new EventBus();
    }
    return *instance;
}

void EventBus::subscribe(IEventListener* listener, EventType eventType) {
    listeners[eventType].push_back(listener);
}

void EventBus::unsubscribe(IEventListener* listener, EventType eventType) {
    if (listeners.count(eventType)) {
        auto& listenerList = listeners[eventType];
        // Remove the listener from the list
        for (auto it = listenerList.begin(); it != listenerList.end(); ++it) {
            if (*it == listener) {
                listenerList.erase(it);
                break;
            }
        }
    }
}

void EventBus::publish(const Event& event) {
    if (listeners.count(event.type)) {
        for (IEventListener* listener : listeners[event.type]) {
            listener->handleEvent(event);
        }
    }
}