#pragma once

#include "UIElement.hpp"
#include <string>

class DefaultSettingView : public UIElement {
private:
    std::string textValue;

public:
    DefaultSettingView(const std::string& text = "");
    void draw(IDisplay& display) override;
    void setText(const std::string& text) override;
    std::string getText() const override;
};