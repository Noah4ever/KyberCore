#pragma once

#include "components/blade/IBlade.hpp"
#include <FastLED.h>
#include <ArduinoJson.h>

class Neopixel : public IBlade {
private:
    CRGB* leds;
    int numLeds;
    int brightness;

public:
    Neopixel(const ArduinoJson::JsonObjectConst& config);
    ~Neopixel() override;

    void setup() override;
    void update() override;

    BladeType getType() const override { return BladeType::NEOPIXEL; }
    int getNumLeds() const override;
    void setColor(CRGB color) override;
    void setPixelColor(int pixel, CRGB color);
    void setBrightness(int brightness) override;
    void show() override;

private:
    CRGB Wheel(byte WheelPos);
};