#pragma once

#include "UIElement.hpp"
#include <string>


class MenuItem : public UIElement {
private:
    std::string text;
    UIStyle currentStyle = UIStyle::Default;

public:
    MenuItem(const std::string& label);
    ~MenuItem() override = default;

    void draw(IDisplay& display) override;
    void setText(const std::string& newText);
    std::string getText() const;

    // Override handleInput if menu item itself needs to react to input
    void handleInput(int encoderDelta, bool buttonPressed, bool longPressed) override {}
};