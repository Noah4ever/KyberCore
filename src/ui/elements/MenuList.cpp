#include "ui/elements/MenuList.hpp"
#include "ui/elements/MenuItem.hpp"
#include "components/display/IDisplay.hpp"

MenuList::MenuList() {}

MenuList::~MenuList() {
    for (auto& item : items) {
        delete item; // Clean up allocated MenuItem objects
    }
    items.clear();
}

void MenuList::draw(IDisplay& display) {
    int startY = y - scrollOffset;
    for (size_t i = 0; i < items.size(); ++i) {
        if (startY >= y && startY < y + height) { // Only draw visible items
            items[i]->setPosition(x, startY);
            if (static_cast<int>(i) == selectedIndexValue) {
                items[i]->setStyle(UIStyle::Selected);
                items[i]->setSize(width, itemHeight); // Set width and height for highlight
            } else {
                items[i]->setStyle(UIStyle::Default);
                items[i]->setSize(width, itemHeight);
            }
            items[i]->draw(display);
        }
        startY += itemHeight;
    }
}

void MenuList::setItems(const std::vector<std::string>& newItems) {
    for (auto& item : items) {
        delete item;
    }
    items.clear();
    for (const auto& text : newItems) {
        items.push_back(new MenuItem(text));
    }
    selectedIndexValue = 0;
    scrollOffset = 0;
}

void MenuList::setSelectedIndex(int index) {
    if (!items.empty()) {
        selectedIndexValue = constrain(index, 0, static_cast<int>(items.size()) - 1);
        // Adjust scrollOffset to keep the selected item visible (basic example)
        if (selectedIndexValue * itemHeight < scrollOffset) {
            scrollOffset = selectedIndexValue * itemHeight;
        } else if ((selectedIndexValue + 1) * itemHeight > scrollOffset + height) {
            scrollOffset = (selectedIndexValue + 1) * itemHeight - height;
        }
    }
}

int MenuList::getSelectedIndex() const {
    return selectedIndexValue;
}

void MenuList::handleInput(int encoderDelta, bool buttonPressed, bool longPressed) {
    if (!items.empty()) {
        if (encoderDelta != 0) {
            setSelectedIndex(selectedIndexValue + encoderDelta);
        }
        if (buttonPressed && onItemSelected) {
            onItemSelected(selectedIndexValue);
        }
        // Handle long press if needed
    }
}