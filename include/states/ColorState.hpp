#pragma once

#include "states/SettingState.hpp"
#include "components/display/IDisplay.hpp"
#include "events/EventType.hpp"

class ColorState : public SettingState
{
private:
    ColorData currentColor;
    constexpr static ColorData DEFAULT_COLOR = {255, 0, 0}; // Default color index
    const ColorData POSSIBLE_COLORS[38] = {
        {255, 0, 0},     // Red
        {255, 16, 0},    // Red-Red-Red-Orange
        {255, 32, 0},    // Red-Red-Orange
        {255, 64, 0},    // Red-Orange
        {255, 127, 0},   // Orange
        {255, 191, 0},   // Orange-Yellow
        {255, 255, 0},   // Yellow
        {191, 255, 0},   // Yellow-Green
        {127, 255, 0},   // Chartreuse
        {64, 255, 0},    // Green-Yellow
        {0, 255, 0},     // Green
        {0, 255, 16},    // Green-Lime
        {0, 255, 32},    // Lime
        {0, 255, 64},    // Cyan
        {0, 255, 127},   // Spring Green
        {0, 255, 191},   // Cyan-Green
        {0, 255, 255},   // Cyan
        {64, 255, 255},   // Cyan-White
        {127, 255, 255},  // Cyan-White
        {255, 255, 255},  // White
        {127, 225, 255},  // Magenta-White
        {64, 205, 255},   // Magenta-Cyan
        {0, 191, 255},   // Cyan-Blue
        {0, 127, 255},   // Azure
        {0, 64, 255},    // Blue-Azure
        {0, 32, 255},    // Blue-Blue-Azure
        {0, 0, 255},     // Blue
        {32, 0, 255},    // Blue-Blue-Violet
        {64, 0, 255},    // Blue-Violet
        {96, 0, 255},    // Violet-Blue
        {127, 0, 255},   // Violet
        {191, 0, 255},   // Violet-Magenta
        {255, 0, 255},   // Magenta
        {255, 0, 191},   // Magenta-Rose
        {255, 0, 127},   // Rose
        {255, 0, 64},    // Rose-Red
        {255, 0, 32},    // Rose-Red-Red
        {255, 0, 16}     // Rose-Red-Red-Red
    };
    
    size_t NUM_POSSIBLE_COLORS;
    size_t targetColorIndex = 0;
    size_t startColorIndex = 0; // Start color index for animation
    float animationProgress = 1.0f;     // Animation progress (0.0-1.0)
    const float ANIMATION_SPEED = 0.025f; // Animation speed (0.0-1.0 per update)
    bool isAnimating = false;

public:
    ColorState();

    void handleRotation(int delta) override;
    void handleButtonPress() override;
    void update() override;
    void updateDisplayData() override;
    void resetState() override;
};
