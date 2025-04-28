#pragma once

#include "UIElement.hpp"
#include <String>

class ProgressBar : public UIElement {
private:
    int valueValue;
    int minValue;
    int maxValue;
    std::string labelText;

public:
    ProgressBar(int value, int min, int max, int w, int h, const std::string& label = "");
    void draw(IDisplay& display) override;
    void clear(IDisplay& display) override;
    void setValue(int value) override;
    int getValue() const override;
    void setLabel(const std::string& label);
};