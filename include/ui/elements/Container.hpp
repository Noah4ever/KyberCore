#pragma once

#include "UIElement.hpp"

class Container : public UIElement {
public:
    void draw(IDisplay& display) override;
};