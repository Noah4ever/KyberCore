#include "ui/elements/UIElement.hpp"

void UIElement::clear(IDisplay &display)
{
    display.drawFillRect(x, y, width, height, UIColor::Black);
}
