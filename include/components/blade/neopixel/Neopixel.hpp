#pragma once

#include "components/blade/IBlade.hpp"
#include "states/ColorState.hpp"
#include <FastLED.h>
#include <ArduinoJson.h>

class Neopixel : public IBlade {
private:
    CRGB* leds;
    ColorData color;
    int numLeds;
    int brightness;

public:
    Neopixel(const ArduinoJson::JsonObjectConst& config);
    ~Neopixel() override;

    void setup() override;
    void update() override;

    BladeType getType() const override { return BladeType::NEOPIXEL; }
    int getNumLeds() const;
    void setInitColor(ColorData color) override;
    void setColor(ColorData color, bool force) override;
    ColorData getColor() const override {
        return color;
    }
    void setPixelColor(int pixel, CRGB color, bool force = false);
    void setBrightness(int brightness, bool force = false) override;
    void show() override;

private:
    CRGB Wheel(byte WheelPos);
};