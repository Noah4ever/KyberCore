#include "components/blade/neopixel/Neopixel.hpp"
#include "core/ComponentRegistrar.hpp"

#include <Arduino.h>
#include <FastLED.h>
#include <ArduinoJson.h>

Neopixel::Neopixel(const ArduinoJson::JsonObjectConst& config)
    : numLeds(config["neopixel"]["numLeds"] | 120)
    , brightness(config["neopixel"]["brightness"] | 80)
    {
    leds = new CRGB[numLeds];
}

Neopixel::~Neopixel()  {
    delete[] leds;
}

#define DATA_PIN 2

void Neopixel::setup()  {

    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, numLeds);
    FastLED.setBrightness(brightness);
    FastLED.clear();
    FastLED.show();
}

void Neopixel::update()  {
    // This is just test to see if the LEDs are working
    // Animations should be handled in a separate class
    static unsigned long lastUpdateTime = 0;
    static int currentLedIndex = 0;
    unsigned long currentTime = millis();
    const unsigned long intervalMs = 50; // Time interval in milliseconds

    if (currentTime - lastUpdateTime >= intervalMs) {
        if (currentLedIndex < numLeds) {
            leds[currentLedIndex] = CRGB::Red;
            FastLED.show();
            currentLedIndex++;
            lastUpdateTime = currentTime;
        } else {
            // If all LEDs have been cycled through, you can define the behavior
            // for the next "update" round here.
            // For example, turn them all off again or restart the sequence.
            // At this point, we simply let them shine blue.
        }
    }
}

int Neopixel::getNumLeds() const  {
    return numLeds;
}

void Neopixel::setColor(CRGB color)  {
    for (int i = 0; i < numLeds; i++) {
        leds[i] = color;
    }
}

void Neopixel::setPixelColor(int pixel, CRGB color) {
    if (pixel >= 0 && pixel < numLeds) {
        leds[pixel] = color;
    }
}

void Neopixel::setBrightness(int brightness)  {
    FastLED.setBrightness(brightness);
    this->brightness = brightness;
}

void Neopixel::show()  {
    FastLED.show();
}

CRGB Neopixel::Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
        WheelPos -= 170;
        return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}

static ComponentRegistrar<ComponentType::BLADE_NEOPIXEL> registrar( "neopixel",
    [](const ArduinoJson::JsonObjectConst& config) -> IComponent* {
        return new Neopixel(config);
    }
);