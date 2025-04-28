#include "components/blade/neopixel/animations/NeopixelExtinguishAnimation.hpp"
#include "components/blade/neopixel/Neopixel.hpp"
#include <Arduino.h>
#include <FastLED.h>

void NeopixelExtinguishAnimation::play(IBlade *blade, const ArduinoJson::JsonObjectConst &config)
{
    Neopixel *neopixelBlade = static_cast<Neopixel *>(blade);
    if (neopixelBlade)
    {
        Serial.println("NeopixelExtinguishAnimation::play() called with neopixel");
        startTime = millis();
        playing = true;
        ledsLitCount = 0; // Start with 0 extinguished
        lastLedExtinguishTime = 0;
        durationMs = DEFAULT_DURATION_MS;
    }
}

void NeopixelExtinguishAnimation::update(IBlade *blade)
{
    if (playing)
    {
        Neopixel *neopixelBlade = static_cast<Neopixel *>(blade);
        if (neopixelBlade)
        {
            unsigned long currentTime = millis();
            int numLeds = neopixelBlade->getNumLeds();
            unsigned long intervalBetweenLedsMs = durationMs / numLeds;
            if (intervalBetweenLedsMs < 10)
                intervalBetweenLedsMs = 10;

            if (ledsLitCount < numLeds)
            {
                if (currentTime - lastLedExtinguishTime >= intervalBetweenLedsMs)
                {
                    int ledIndexToExtinguish = numLeds - 1 - ledsLitCount; // Start from the last LED
                    neopixelBlade->setPixelColor(ledIndexToExtinguish, CRGB(0, 0, 0), true); // Set the LED to black (off)
                    neopixelBlade->show();
                    ledsLitCount++;
                    lastLedExtinguishTime = currentTime;
                }
            }
            else
            {
                playing = false;
            }
        }
    }
}

bool NeopixelExtinguishAnimation::isPlaying() const
{
    return playing;
}

void NeopixelExtinguishAnimation::stop()
{
    playing = false;
}