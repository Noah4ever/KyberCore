#pragma once

#include "UIElement.hpp"
#include "MenuItem.hpp" // Include the MenuItem header
#include <vector>
#include <string>
#include <functional>

class MenuList : public UIElement {
private:
    std::vector<MenuItem*> items; // Store MenuItem pointers
    int selectedIndexValue = 0;
    int itemHeight = 10; // Standardhöhe für Menüeinträge
    int scrollOffset = 0; // Für längere Listen
    int visibleItems = 3; // Number of items visible at once

public:
    std::function<void(int)> onItemSelected;

    MenuList();
    ~MenuList() override;
    void draw(IDisplay& display) override;
    void setItems(const std::vector<std::string>& newItems);
    void setSelectedIndex(int index);
    int getSelectedIndex() const;
    void handleInput(int encoderDelta, bool buttonPressed, bool longPressed) override;
};