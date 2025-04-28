#include "components/blade/neopixel/animations/NeopixelRainbowAnimation.hpp"
#include "components/blade/neopixel/Neopixel.hpp"
#include <Arduino.h>
#include <FastLED.h>

void NeopixelRainbowAnimation::play(IBlade *blade, const ArduinoJson::JsonObjectConst &config)
{
    Neopixel *neopixelBlade = static_cast<Neopixel *>(blade);
    if (neopixelBlade)
    {
        Serial.println("NeopixelRainbowAnimation::play() called with neopixel");
        startTime = millis();
        playing = true;
        numLeds = neopixelBlade->getNumLeds();
        speed = DEFAULT_SPEED; // Default speed
        segmentLength = DEFAULT_SEGMENT_LENGTH; // Default rainbow segment length

        if (config.containsKey("speed"))
        {
            speed = config["speed"].as<float>();
        }

        if (config.containsKey("segment_length"))
        {
            segmentLength = config["segment_length"].as<int>();
        }

        hueOffset = 0; // Start at the beginning of the rainbow
    }
}

void NeopixelRainbowAnimation::update(IBlade *blade)
{
    if (playing)
    {
        Neopixel *neopixelBlade = static_cast<Neopixel *>(blade);
        if (neopixelBlade)
        {
            unsigned long currentTime = millis();
            float timeDelta = (currentTime - startTime) / 1000.0f; // Time in seconds
            hueOffset = fmod(timeDelta * speed * 255, 255); // Move through the hue spectrum

            for (int i = 0; i < numLeds; ++i)
            {
                uint8_t hue = static_cast<uint8_t>(fmod(hueOffset + (float)i * (255.0f / segmentLength), 255));
                neopixelBlade->setPixelColor(i, CHSV(hue, 255, 255), true); // Full saturation and brightness
            }
            neopixelBlade->show();
        }
    }
}

bool NeopixelRainbowAnimation::isPlaying() const
{
    return playing;
}

void NeopixelRainbowAnimation::stop()
{
    playing = false;
}