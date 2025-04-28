#include "ui/elements/TextLabel.hpp"

TextLabel::TextLabel(const std::string& text) : textValue(text) {}

void TextLabel::draw(IDisplay& display) {
    display.drawTextInternal(x, y, textValue);
}

void TextLabel::setText(const std::string& text) {
    textValue = text;
}

std::string TextLabel::getText() const {
    return textValue;
}