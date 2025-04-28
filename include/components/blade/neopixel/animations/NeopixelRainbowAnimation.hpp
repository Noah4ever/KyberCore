#pragma once

#include "components/blade/animations/IAnimation.hpp"
#include "components/blade/neopixel/Neopixel.hpp"
#include <ArduinoJson.h>

class NeopixelRainbowAnimation : public IAnimation {
private:
    unsigned long startTime = 0;
    bool playing = false;
    int numLeds = 0;
    float speed = 0.5f; // Speed of the rainbow movement (adjust as needed)
    int segmentLength = 10; // Length of each color segment in LEDs
    float hueOffset = 0;

    constexpr static float DEFAULT_SPEED = 0.5f;
    constexpr static int DEFAULT_SEGMENT_LENGTH = 10;

public:
    void play(IBlade* blade, const ArduinoJson::JsonObjectConst& config) override;
    void update(IBlade* blade) override;
    bool isPlaying() const override;
    void stop() override;
};