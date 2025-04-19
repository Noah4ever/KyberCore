#pragma once

#include "components/IComponent.hpp"

#include <string>

class IDisplay : public IComponent
{
public:
    virtual ~IDisplay() = default;

    virtual void clear() = 0;
    virtual void drawString(int x, int y, const char *str) = 0;
    virtual void drawString(int x, int y, const std::string &str) = 0;
    virtual void display() = 0;

    virtual void setup() override = 0;
    virtual void update() override = 0;
};