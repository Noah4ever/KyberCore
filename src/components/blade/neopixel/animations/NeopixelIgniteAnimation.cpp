#include "components/blade/neopixel/animations/NeopixelIgniteAnimation.hpp"
#include "components/blade/neopixel/Neopixel.hpp"
#include <Arduino.h>
#include <FastLED.h>

void NeopixelIgniteAnimation::play(IBlade *blade, const ArduinoJson::JsonObjectConst &config)
{
    Neopixel *neopixelBlade = static_cast<Neopixel *>(blade);
    if (neopixelBlade)
    {
        startTime = millis();
        playing = true;
        ledsLitCount = 0;
        lastLedLitTime = 0;
        durationMs = DEFAULT_DURATION_MS;

        if (config.containsKey("duration"))
        {
            durationMs = config["duration"].as<unsigned long>();
        }

        uint8_t redValue;
        if (config.containsKey("color") && config["color"].containsKey("r"))
        {
            redValue = config["color"]["r"].as<uint8_t>();
        }
        else if (blade != nullptr)
        {
            redValue = blade->getColor().red;
        }
        else
        {
            redValue = 255;
        }
        igniteColor.red = redValue;

        uint8_t greenValue;
        if (config.containsKey("color") && config["color"].containsKey("g"))
        {
            greenValue = config["color"]["g"].as<uint8_t>();
        }
        else if (blade != nullptr)
        {
            greenValue = blade->getColor().green;
        }
        else
        {
            greenValue = 255;
        }
        igniteColor.green = greenValue;

        uint8_t blueValue;
        if (config.containsKey("color") && config["color"].containsKey("b"))
        {
            blueValue = config["color"]["b"].as<uint8_t>();
        }
        else if (blade != nullptr)
        {
            blueValue = blade->getColor().blue;
        }
        else
        {
            blueValue = 255;
        }
        igniteColor.blue = blueValue;
        if (igniteColor.red == 0 && igniteColor.green == 0 && igniteColor.blue == 0)
        {
            igniteColor = {255, 255, 255};
        }

        for (int i = 0; i < neopixelBlade->getNumLeds(); i++)
        {
            neopixelBlade->setPixelColor(i, CRGB::Black);
        }
        neopixelBlade->show();
    }
}

void NeopixelIgniteAnimation::update(IBlade *blade)
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
                if (currentTime - lastLedLitTime >= intervalBetweenLedsMs)
                {
                    neopixelBlade->setPixelColor(ledsLitCount, CRGB(igniteColor.red, igniteColor.green, igniteColor.blue));
                    neopixelBlade->show();
                    ledsLitCount++;
                    lastLedLitTime = currentTime;
                }
            }
            else
            {
                playing = false;
            }
        }
    }
}

bool NeopixelIgniteAnimation::isPlaying() const
{
    return playing;
}

void NeopixelIgniteAnimation::stop()
{
    playing = false;
}