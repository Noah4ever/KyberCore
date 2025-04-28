
#include "states/ColorState.hpp"
#include "events/EventBus.hpp"
#include "Arduino.h" // For Serial print
#include "ui/elements/DefaultSettingView.hpp"
#include "ui/elements/MenuList.hpp"
#include <cmath> 

ColorState::ColorState() : currentColor(DEFAULT_COLOR) 
{
    NUM_POSSIBLE_COLORS = sizeof(POSSIBLE_COLORS) / sizeof(POSSIBLE_COLORS[0]);
    Event colorEvent(EventType::INIT_COLOR_CHANGED, DataType::COLOR_VALUE);
    colorEvent.colorData = currentColor;
    EventBus::getInstance().publish(colorEvent);

    defaultUI = new DefaultSettingView("Color");
    colorInfoLabel = new TextLabel();
    colorInfoLabel->x = 7;
    colorInfoLabel->y = 20;
    colorInfoLabel->width = 117;
    colorInfoLabel->height = 10;
    const String colorInfo = " R:" + String(currentColor.red) + ", G:" + String(currentColor.green) + ", B:" + String(currentColor.blue);
    colorInfoLabel->setText(colorInfo.c_str());
    defaultUI->addChild(colorInfoLabel);

    menuUI = new MenuList();
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
            Event requestUI(EventType::DISPLAY_REQUEST_UPDATE, DataType::NONE);
            EventBus::getInstance().publish(requestUI);
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
            Event requestUI(EventType::DISPLAY_REQUEST_UPDATE, DataType::NONE);
            EventBus::getInstance().publish(requestUI);
            publishColorEvent();
        } else {
            currentColor = lerpColor(POSSIBLE_COLORS[startColorIndex], POSSIBLE_COLORS[targetColorIndex], animationProgress);
            publishColorEvent();
        }
    }
}

void ColorState::handleButtonPress() 
{
    
}

void ColorState::updateDisplay(IDisplay* display) 
{
    if (display) {
        const ColorData color = POSSIBLE_COLORS[targetColorIndex];
        colorInfoLabel->clear(*display);
        String colorInfo = "R:" + String(color.red) + ", G:" + String(color.green) + ", B:" + String(color.blue);
        colorInfoLabel->setText(colorInfo.c_str());
        colorInfoLabel->draw(*display);
        display->displayInternal();
    }
}

UIElement *ColorState::getDefaultUI()
{
    return defaultUI;
}

UIElement *ColorState::getMenuUI()
{
    return menuUI;
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