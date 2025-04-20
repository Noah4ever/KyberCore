#pragma once

class IComponent {
    public:
        virtual ~IComponent() = default; // Ensure proper cleanup of derived classes
        virtual void setup() = 0;
        virtual void update() = 0;
};