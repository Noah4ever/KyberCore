#include "ui/elements/ProgressBar.hpp"
#include "Arduino.h" 

ProgressBar::ProgressBar(int value, int min, int max, int w, int h, const std::string& label)
    : valueValue(value), minValue(min), maxValue(max), labelText(label) {
    width = w;
    height = h;
}

void ProgressBar::draw(IDisplay& display) {
    int barWidth = map(valueValue, minValue, maxValue, 0, width - 4);
    display.drawRect(x, y, width, height, 4); // Outline
    display.drawFillRect(x + 2, y + 2, barWidth, height - 4, 4); // Fill
    if (!labelText.empty()) {
        display.drawTextInternal(x + 2, y + 2, labelText); // Label
    }
}

void ProgressBar::clear(IDisplay& display) {
    display.drawFillRect(x + 2, y + 2, width - 4, height - 4, UIColor::Black); // Clear the filled area
}

void ProgressBar::setValue(int value)  {
    valueValue = constrain(value, minValue, maxValue);
}

int ProgressBar::getValue() const  {
    return valueValue;
}

void ProgressBar::setLabel(const std::string& label) {
    labelText = label;
}