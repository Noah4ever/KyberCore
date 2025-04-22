#include "components/display/IDisplay.hpp"
#include "events/EventType.hpp"

void IDisplay::displayUIElements(const std::vector<UIElement>& elements) {
    clearDisplayInternal();
    for (const auto& element : elements) {
        switch (element.type) {
            case UIElement::Type::PROGRESS_BAR:
                drawProgressBarInternal(element.x, element.y, element.progressBarWidth, element.progressBarHeight, element.progressBarValue);
                break;
            case UIElement::Type::ICON:
                drawIconInternal(element.x, element.y, element.iconData, element.iconWidth, element.iconHeight);
                break;
            case UIElement::Type::TEXT:
                drawTextInternal(element.x, element.y, element.text, 2);
                break;
            case UIElement::Type::VALUE:
                drawValueInternal(element.x, element.y, element.value, 2);
                break;
            default:
                break;
        }
    }
    displayInternal();
}

void IDisplay::handleEvent(const Event& event) {
    switch (event.type) {
        case EventType::DISPLAY_CLEAR_REQUESTED:
            clear();
            break;
        case EventType::DISPLAY_UI_REQUESTED:
        if (event.dataType == DataType::DISPLAY_UI_DATA && !event.displayUIData.elements.empty()) {
            displayUIElements(event.displayUIData.elements);
        }
            break;
        default:
            break;
    }
}