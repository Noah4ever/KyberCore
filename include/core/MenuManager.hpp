#pragma once

#include "core/DisplayManager.hpp"
#include "ui/elements/UIElement.hpp"
#include "core/SettingsStateMachine.hpp"
#include "states/SettingState.hpp"      

class MenuManager {
private:
    SettingsStateMachine* stateMachine;
    DisplayManager* displayManager;
    UIElement* currentMenuUI = nullptr;
    
    int selectedMenuItemIndex = 0;
    bool isMenuOpen = false;

public:
    MenuManager(SettingsStateMachine* sm, DisplayManager* dm);
    ~MenuManager() = default;

    void openMenu();
    void closeMenu();
    void handleRotation(int delta);
    void handleButtonPress();

private:
    void updateMenuUI(); // Internal method to update the visual menu
    void requestDisplayUpdate(); // Use the DisplayManager to request an update
    UIElement* getCurrentStateMenuUI(); // Helper to get the menu UI from the current state
};