#pragma once

#include "UIElement.hpp"
#include "components/display/IDisplay.hpp"

#include <String>
#include <functional>

class Button : public UIElement {
private:
    std::string textValue;
    bool isPressed = false;

public:
    std::function<void()> onClicked;

    Button(const std::string& text = "");
    void draw(IDisplay& display) override;
    void setText(const std::string& text) override;
    std::string getText() const override;
    void handleInput(int encoderDelta, bool buttonPressed, bool longPressed) override;
};