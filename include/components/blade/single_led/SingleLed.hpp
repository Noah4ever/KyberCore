#pragma once

#include "components/blade/IBlade.hpp"
#include <FastLED.h> 
#include <ArduinoJson.h>

class SingleLed : public IBlade {
private:
    int controlPin; // Pin to control the LED
    int currentBrightness = 0;
    CRGB currentColor = CRGB::Black;

public:
    SingleLed(const ArduinoJson::JsonObjectConst& config);
    ~SingleLed() override = default;

    void setup() override;
    void update() override;

    BladeType getType() const override { return BladeType::SINGLE_LED; }
    int getNumLeds() const override { return 1; }
    void setColor(CRGB color) override;
    void setBrightness(int brightness) override;
    void show() override;
};
