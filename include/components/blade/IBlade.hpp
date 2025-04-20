#pragma once

#include "components/IComponent.hpp"
#include "components/blade/BladeType.hpp"
#include <FastLED.h>

class IBlade : public IComponent {
public:
    virtual ~IBlade() = default;
    virtual BladeType getType() const = 0;
    virtual int getNumLeds() const = 0;
    virtual void setColor(CRGB color) = 0;
    virtual void setBrightness(int brightness) = 0;
    virtual void show() = 0;
};