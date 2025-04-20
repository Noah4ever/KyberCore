#pragma once

#include "components/blade/animations/IAnimation.hpp"
#include "components/blade/neopixel/Neopixel.hpp"

class NeopixelIgniteAnimation : public IAnimation {
    private:
        unsigned long startTime = 0;
        unsigned long durationMs = 0;
        bool playing = false;
        CRGB igniteColor = CRGB::White; // Standard Ignite-Farbe
        unsigned long ledsLitCount = 0;
        unsigned long lastLedLitTime = 0;
    
    public:
        void play(IBlade* blade, unsigned long duration, const ArduinoJson::JsonObjectConst& config = ArduinoJson::JsonObjectConst()) override;
        void update(IBlade* blade) override;
        bool isPlaying() const override;
        void stop() override;
    };
    
