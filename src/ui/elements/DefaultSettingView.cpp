#include "ui/elements/DefaultSettingView.hpp"

DefaultSettingView::DefaultSettingView(const std::string& text) : textValue(text) {}

void DefaultSettingView::draw(IDisplay& display) {
    display.drawRect(1, 1, 126, 30, 4);
    display.drawTextInternal(4, 4, "< " + textValue + " >", 1);   
}

void DefaultSettingView::setText(const std::string& text) {
    textValue = text;
}

std::string DefaultSettingView::getText() const {
    return textValue;
}