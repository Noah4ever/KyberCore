#pragma once

#include "components/IComponent.hpp"
#include "events/IEventListener.hpp"
#include "events/EventType.hpp"
#include <string>
#include <ArduinoJson.h>

enum class UIColor
{
    Black = 0,
    White,
    Inverse
};

class IDisplay : public IComponent, public IEventListener
{
public:
    virtual ~IDisplay() = default;

    // Abstract drawing methods - to be implemented by subclasses
    virtual void clearDisplayInternal() = 0;
    virtual void drawIconInternal(int x, int y, const uint8_t *icon, int width, int height) = 0;
    virtual void drawProgressBarInternal(int x, int y, int width, int height, int progress) = 0;
    virtual void drawValueInternal(int x, int y, int value) = 0;
    virtual void drawValueInternal(int x, int y, int value, uint8_t textSize) = 0;
    virtual void drawTextInternal(int x, int y, const std::string &text) = 0;
    virtual void drawTextInternal(int x, int y, const std::string &text, uint8_t textSize) = 0;
    virtual void displayInternal() = 0;

    virtual void drawRect(int x, int y, int width, int height) = 0;
    virtual void drawRect(int x, int y, int width, int height, int radius) = 0;
    virtual void drawFillRect(int x, int y, int width, int height) = 0;
    virtual void drawFillRect(int x, int y, int width, int height, int radius) = 0;
    virtual void drawFillRect(int x, int y, int width, int height, UIColor color) = 0;

    // Public interface
    void clear() { clearDisplayInternal(); }

    // IComponent interface
    virtual void setup() override {}
    virtual void update() override {}

    // IEventListener interface implementation
    void handleEvent(const Event &event) override {}

protected:
    IDisplay() {} // Protected constructor for inheritance
};