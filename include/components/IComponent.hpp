#pragma once

class IComponent {
    public:
        virtual void setup() = 0;
        virtual void update() = 0;
};