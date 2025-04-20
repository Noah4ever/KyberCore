#include "components/blade/neopixel/animations/NeopixelIgniteAnimation.hpp"
#include "components/blade/neopixel/Neopixel.hpp"
#include <Arduino.h>
#include <FastLED.h>

void NeopixelIgniteAnimation::play(IBlade* blade, unsigned long duration, const ArduinoJson::JsonObjectConst& config) {
    Neopixel* neopixelBlade = static_cast<Neopixel*>(blade);
    if (neopixelBlade) {
        startTime = millis();
        durationMs = duration;
        playing = true;
        igniteColor.r = config["color"]["r"] | 255;
        igniteColor.g = config["color"]["g"] | 255;
        igniteColor.b = config["color"]["b"] | 255;

        int numLeds = neopixelBlade->getNumLeds();
        for (int i = 0; i < numLeds; ++i) {
            neopixelBlade->setPixelColor(i, CRGB::Black);
        }
        neopixelBlade->show();
    }
}

void NeopixelIgniteAnimation::update(IBlade* blade) {
    if (playing) {
        Neopixel* neopixelBlade = static_cast<Neopixel*>(blade);
        if (neopixelBlade) {
            unsigned long currentTime = millis();
            int numLeds = neopixelBlade->getNumLeds();
            unsigned long intervalBetweenLedsMs = durationMs / numLeds; // Gleichmäßige Verteilung über die Zeit
            if (intervalBetweenLedsMs < 10) intervalBetweenLedsMs = 10; // Minimale Verzögerung

            if (ledsLitCount < numLeds) {
                if (currentTime - lastLedLitTime >= intervalBetweenLedsMs) {
                    neopixelBlade->setPixelColor(ledsLitCount, igniteColor);
                    neopixelBlade->show();
                    ledsLitCount++;
                    lastLedLitTime = currentTime;
                }
            } else {
                playing = false; // Animation beendet
            }
        }
    }
}

bool NeopixelIgniteAnimation::isPlaying() const {
    return playing;
}

void NeopixelIgniteAnimation::stop() {
    playing = false;
}