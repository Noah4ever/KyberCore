#include "ui/elements/MenuItem.hpp"

MenuItem::MenuItem(const std::string& label) : text(label) {}

void MenuItem::draw(IDisplay& display) {
    int yOffset = y;
    switch (currentStyle) {
        case UIStyle::Default:
            display.drawTextInternal(x, yOffset, text);
            break;
        case UIStyle::Selected:
            display.drawRect(x - 2, yOffset - 1, width + 4, height + 2); // Highlight box
            display.drawTextInternal(x, yOffset, text);
            break;
    }
}

void MenuItem::setText(const std::string& newText) {
    text = newText;
}

std::string MenuItem::getText() const {
    return text;
}
