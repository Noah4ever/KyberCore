#include "core/MenuManager.hpp"
#include "core/SettingsStateMachine.hpp"
#include "states/SettingState.hpp"
#include "ui/elements/Container.hpp"
#include "ui/elements/MenuItem.hpp"  // Assuming you have a MenuItem UI element
#include "core/DisplayManager.hpp"
#include "Arduino.h"

MenuManager::MenuManager(SettingsStateMachine* sm, DisplayManager* dm)
    : stateMachine(sm), displayManager(dm), selectedMenuItemIndex(0) {}

void MenuManager::openMenu() {
    if (stateMachine && stateMachine->getCurrentState()) {
        currentMenuUI = getCurrentStateMenuUI();
        selectedMenuItemIndex = 0; // Reset selection on opening
        updateMenuUI();
        requestDisplayUpdate();
    } else {
        Serial.println("Error: No current state to open menu from.");
    }
}

void MenuManager::closeMenu() {
    currentMenuUI = nullptr;
    selectedMenuItemIndex = 0;
    requestDisplayUpdate(); // Clear the menu
}

void MenuManager::handleRotation(int delta) {
    // if (currentMenuUI) {
    //     int numItems = getNumberOfMenuItems();
    //     if (numItems > 0) {
    //         selectedMenuItemIndex += delta;
    //         if (selectedMenuItemIndex < 0) {
    //             selectedMenuItemIndex = numItems - 1;
    //         } else if (selectedMenuItemIndex >= numItems) {
    //             selectedMenuItemIndex = 0;
    //         }
    //         updateMenuUI();
    //         requestDisplayUpdate();
    //     }
    // }
}

void MenuManager::handleButtonPress() {
    if (currentMenuUI) {
        // Implement logic for what happens when a menu item is selected
        // This will likely depend on the structure of your menu items.
        Serial.print("Menu item selected at index: ");
        Serial.println(selectedMenuItemIndex);

        // Example: If your menu items have a callback or an associated action
        // you would trigger that here.

        // For now, let's just close the menu after a selection
        closeMenu();
    }
}

void MenuManager::requestDisplayUpdate() {
    if (displayManager) {
        Event requestUpdateEvent(EventType::DISPLAY_REQUEST_UPDATE, DataType::NONE);
        EventBus::getInstance().publish(requestUpdateEvent);
    } else {
        Serial.println("Error: DisplayManager not set in MenuManager.");
    }
}

void MenuManager::updateMenuUI() {
    if (currentMenuUI) {
        // This is a basic example. You'll likely need to adapt this
        // based on how your menu UI is structured (e.g., using MenuItem elements).
        Container* menuContainer = static_cast<Container*>(currentMenuUI);
        // Ensure currentMenuUI is actually a Container before casting
        if (menuContainer == nullptr) {
            Serial.println("Error: currentMenuUI is not a Container.");
            return;
        }
        if (menuContainer) {
            for (size_t i = 0; i < menuContainer->getChildren().size(); ++i) {
                UIElement* item = menuContainer->getChildren()[i];
                // Assuming your MenuItem has a way to indicate selection
                // You might need to downcast to a specific MenuItem type
                if (static_cast<int>(i) == selectedMenuItemIndex) {
                    item->setStyle(UIStyle::Selected); // Example: Set a "Selected" style
                } else {
                    item->setStyle(UIStyle::Default);  // Example: Set a "Default" style
                }
            }
        }
    }
}

UIElement* MenuManager::getCurrentStateMenuUI() {
    if (stateMachine && stateMachine->getCurrentState()) {
        // Assuming your SettingState has a method to get the menu UI
        return stateMachine->getCurrentState()->getMenuUI();
    }
    return nullptr;
}