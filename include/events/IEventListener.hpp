#pragma once

#include "events/EventBus.hpp" 

class IEventListener {
public:
    virtual ~IEventListener() = default;

    /**
     * @brief This method is called when an event occurs.
     *
     * @param event The event that occurred and contains the event type and data.
     */
    virtual void handleEvent(const Event& event) = 0;
};
