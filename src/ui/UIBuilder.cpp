#include "ui/UIBuilder.hpp"

UIBuilder::UIBuilder() {}

UIBuilder& UIBuilder::addProgressBar(int x, int y, int width, int height, int value) {
    elements.push_back({UIElement::Type::PROGRESS_BAR, x, y, width, height, value});
    return *this;
}

UIBuilder& UIBuilder::addIcon(int x, int y, const uint8_t* data, int width, int height) {
    elements.push_back({UIElement::Type::ICON, x, y, 0, 0, 0, data, width, height});
    return *this;
}

UIBuilder& UIBuilder::addText(int x, int y, const std::string& text) {
    elements.push_back({UIElement::Type::TEXT, x, y, 0, 0, 0, nullptr, 0, 0, text});
    return *this;
}

UIBuilder& UIBuilder::addValue(int x, int y, int value) {
    elements.push_back({UIElement::Type::VALUE, x, y, 0, 0, 0, nullptr, 0, 0, std::to_string(value), value});
    return *this;
}

std::vector<UIElement> UIBuilder::build() {
    return elements;
}

void UIBuilder::clear() {
    elements.clear();
}