#include "components/blade/neopixel/Neopixel.hpp"
#include "core/ComponentRegistrar.hpp"
#include <components/blade/neopixel/animations/NeopixelIgniteAnimation.hpp>
#include <components/blade/neopixel/animations/NeopixelExtinguishAnimation.hpp>
#include <components/blade/neopixel/animations/NeopixelRainbowAnimation.hpp>
#include "events/EventBus.hpp"

#include <Arduino.h>
#include <FastLED.h>
#include <ArduinoJson.h>

Neopixel::Neopixel(const ArduinoJson::JsonObjectConst& config)
    : numLeds(config["neopixel"]["numLeds"] | 120)
    , brightness(config["neopixel"]["brightness"] | 80)
    {
    leds = new CRGB[numLeds];

    addAnimation(EventType::BLADE_IGNITE, std::make_unique<NeopixelIgniteAnimation>());
    addAnimation(EventType::BLADE_EXTINGUISH, std::make_unique<NeopixelExtinguishAnimation>());
    addAnimation(EventType::BLADE_RAINBOW_ANIMATION, std::make_unique<NeopixelRainbowAnimation>());
}

Neopixel::~Neopixel()  {
    delete[] leds;
}

#define DATA_PIN 2

void Neopixel::setup()  {

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, numLeds);
    FastLED.setBrightness(brightness);
    FastLED.clear();
    FastLED.show();

    EventBus::getInstance().subscribe(this, EventType::INIT_COLOR_CHANGED);
    EventBus::getInstance().subscribe(this, EventType::COLOR_CHANGED);
    EventBus::getInstance().subscribe(this, EventType::BRIGHTNESS_CHANGED);

    EventBus::getInstance().subscribe(this, EventType::BLADE_IGNITE);
    EventBus::getInstance().subscribe(this, EventType::BLADE_EXTINGUISH);
    EventBus::getInstance().subscribe(this, EventType::BLADE_BLASTER_REFLECT);
    EventBus::getInstance().subscribe(this, EventType::BLADE_RAINBOW_ANIMATION);
}

void Neopixel::update()  {

    IBlade::updateAnimation();
}

int Neopixel::getNumLeds() const  {
    return numLeds;
}

void Neopixel::setInitColor(ColorData color)  {
    this->color = color;
    for (int i = 0; i < numLeds; i++) {
        leds[i] = CRGB(color.red, color.green, color.blue);
    }
}

void Neopixel::setColor(ColorData color, bool force)  {
    this->color = color;
    if(!bladeIsIgnited && !force) {
        return;
    }
    for (int i = 0; i < numLeds; i++) {
        leds[i] = CRGB(color.red, color.green, color.blue);
    }
    FastLED.show();
}

void Neopixel::setPixelColor(int pixel, CRGB color, bool force)  {
    if(!bladeIsIgnited && !force) {
        return;
    }
    if (pixel >= 0 && pixel < numLeds) {
        leds[pixel] = color;
    }

}

void Neopixel::setBrightness(int brightness, bool force)  {
    this->brightness = brightness;
    if(!bladeIsIgnited && !force) {
        return;
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
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