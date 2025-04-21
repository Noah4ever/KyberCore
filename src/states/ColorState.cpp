
#include "states/ColorState.hpp"
#include "events/EventBus.hpp"
#include "Arduino.h" // For Serial print
#include <cmath> 

ColorState::ColorState() : currentColor(DEFAULT_COLOR) 
{
    NUM_POSSIBLE_COLORS = sizeof(POSSIBLE_COLORS) / sizeof(POSSIBLE_COLORS[0]);
}

void ColorState::handleRotation(int delta) 
{
    static size_t currentColorIndex = 0;
    
    if (!isAnimating) {
        size_t previousColorIndex = currentColorIndex; // Store previous color index

        if (delta > 0) {
            currentColorIndex++;
            if (currentColorIndex >= NUM_POSSIBLE_COLORS) {
                currentColorIndex = 0;
            }
        } else if (delta < 0) {
            if (currentColorIndex > 0) {
                currentColorIndex--;
            } else {
                currentColorIndex = NUM_POSSIBLE_COLORS - 1;
            }
        }

        if (previousColorIndex != currentColorIndex) {
            startColorIndex = previousColorIndex; 
            targetColorIndex = currentColorIndex;
            animationProgress = 0.0f; // Start Animation
            isAnimating = true;
        }
    }
}

ColorData lerpColor(const ColorData& a, const ColorData& b, float t) {
    return {
        static_cast<uint8_t>(a.red + (b.red - a.red) * t),
        static_cast<uint8_t>(a.green + (b.green - a.green) * t),
        static_cast<uint8_t>(a.blue + (b.blue - a.blue) * t)
    };
}

void ColorState::update() { 
    if (isAnimating) {
        animationProgress += ANIMATION_SPEED;
        if (animationProgress >= 1.0f) {
            animationProgress = 1.0f;
            isAnimating = false;
            currentColor = POSSIBLE_COLORS[targetColorIndex]; // Set to target color
            Event colorEvent(EventType::COLOR_CHANGED, DataType::COLOR_VALUE);
            colorEvent.colorData = currentColor;
            EventBus::getInstance().publish(colorEvent);
        } else {
            currentColor = lerpColor(POSSIBLE_COLORS[startColorIndex], POSSIBLE_COLORS[targetColorIndex], animationProgress);
            Event colorEvent(EventType::COLOR_CHANGED, DataType::COLOR_VALUE);
            colorEvent.colorData = currentColor;
            EventBus::getInstance().publish(colorEvent);
        }
    }
}

void ColorState::handleButtonPress() 
{
    
}

void ColorState::updateDisplay(IDisplay *display) 
{
   // Update display
}

void ColorState::resetState() 
{
    static size_t currentColorIndex = 0; 
    currentColor = DEFAULT_COLOR;
    Event colorEvent(EventType::COLOR_CHANGED, DataType::COLOR_VALUE);
    colorEvent.colorData = currentColor;
    EventBus::getInstance().publish(colorEvent);
    isAnimating = false;
    animationProgress = 1.0f;
}