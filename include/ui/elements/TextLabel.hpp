#pragma once

#include "UIElement.hpp"
#include <String>

class TextLabel : public UIElement {
private:
    std::string textValue;

public:
    TextLabel(const std::string& text = "");
    void draw(IDisplay& display) override;
    void setText(const std::string& text) override;
    std::string getText() const override;
};