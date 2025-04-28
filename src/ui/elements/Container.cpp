#include "ui/elements/Container.hpp"

void Container::draw(IDisplay& display) {
    // Container selbst zeichnet nichts, dient nur als Layout-Helfer
    for (UIElement* child : children) {
        child->draw(display);
    }
}