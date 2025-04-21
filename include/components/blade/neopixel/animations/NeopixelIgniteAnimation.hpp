#pragma once

#include "components/blade/animations/IAnimation.hpp"
#include "components/blade/neopixel/Neopixel.hpp"
#include <ArduinoJson.h>

class NeopixelIgniteAnimation : public IAnimation {
private:
    unsigned long startTime = 0;
    constexpr static unsigned long DEFAULT_DURATION_MS = 1500; // Default duration in milliseconds
    unsigned long durationMs = DEFAULT_DURATION_MS;
    bool playing = false;
    ColorData igniteColor; // Standard Ignite-Farbe
    unsigned long ledsLitCount = 0;
    unsigned long lastLedLitTime = 0;

public:
    void play(IBlade* blade, const ArduinoJson::JsonObjectConst& config) override; 
    void update(IBlade* blade) override;
    bool isPlaying() const override;
    void stop() override;
};