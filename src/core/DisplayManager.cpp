#include "core/DisplayManager.hpp"

DisplayManager::DisplayManager() : display(nullptr) {}

DisplayManager::~DisplayManager() {
    if (display) {
        delete display;
    }
}

void DisplayManager::setup() {
    EventBus::getInstance().subscribe(this, EventType::DISPLAY_REQUEST_UPDATE);
    EventBus::getInstance().subscribe(this, EventType::STATE_CHANGED);

    if (display) {
        display->setup();
        display->clear();
        // display start up animation
    }
}

void DisplayManager::update() {
}

void DisplayManager::setDisplay(IDisplay* newDisplay) {
    if (display) {
        delete display;
    }
    display = newDisplay;
}

void DisplayManager::setSettingsStateMachine(SettingsStateMachine* settingsStateMachine) {
    this->settingsStateMachine = settingsStateMachine;
}

void DisplayManager::handleEvent(const Event& event) {
    switch (event.type) {
        case EventType::DISPLAY_REQUEST_UPDATE:
            if (currentState) {
                currentState->updateDisplay(display);
            }
            break;
        case EventType::STATE_CHANGED:
            if (settingsStateMachine) {
                currentState = settingsStateMachine->getCurrentState();
                if (currentState) {
                    display->clear();
                    UIElement* defaultUI = currentState->getDefaultUI();
                    if (defaultUI) {
                        defaultUI->draw(*display);
                    }
                    currentState->updateDisplay(display);
                }
            }
            break;
        default:
            break;
    }
}

