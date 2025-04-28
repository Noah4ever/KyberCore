#include "ui/elements/Button.hpp"

Button::Button(const std::string& text) : textValue(text) {}

void Button::draw(IDisplay& display) {
    // display.drawRect(x, y, width, height, UI_Color::UI_WHITE);
    // display.drawString(x + 2, y + 1, textValue);
    // if (isPressed) {
    //     display.fillRect(x + 1, y + 1, width - 2, height - 2, UI_Color::UI_GRAY); // Gedrückter Effekt
    // }
}

void Button::setText(const std::string& text)  {
    textValue = text;
}

std::string Button::getText() const  {
    return textValue;
}

void Button::handleInput(int encoderDelta, bool buttonPressed, bool longPressed)  {
    if (buttonPressed) {
        isPressed = true;
        if (onClicked) {
            onClicked();
        }
    } else {
        isPressed = false;
    }
}