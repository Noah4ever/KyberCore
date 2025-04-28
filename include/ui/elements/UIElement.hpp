#pragma once

#include <string>
#include <vector>
#include "components/display/IDisplay.hpp" // Annahme: IDisplay ist im display Ordner

enum class LayoutDirection
{
    VERTICAL,
    HORIZONTAL
};

enum class UIStyle {
    Default,
    Selected
};

class UIElement
{
public:
    std::string id;
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    LayoutDirection direction = LayoutDirection::VERTICAL;
    UIStyle style = UIStyle::Default;
    std::vector<UIElement *> children;
    UIElement *parent = nullptr;

    virtual ~UIElement() = default;
    virtual void draw(IDisplay &display) {
    }
    virtual void clear(IDisplay &display);
    virtual void handleInput(int encoderDelta, bool buttonPressed, bool longPressed) {} 
    virtual void setValue(int value) {}                                                 
    virtual int getValue() const { return 0; }
    virtual void setText(const std::string &text) {} 
    virtual std::string getText() const { return ""; }
    virtual void update() {}

    virtual void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }
    virtual void setSize(int newWidth, int newHeight) {
        width = newWidth;
        height = newHeight;
    }
    virtual void setDirection(LayoutDirection newDirection) {
        direction = newDirection;
    }
    virtual void setStyle(UIStyle newStyle) {
        style = newStyle;
    }
    virtual UIStyle getStyle(){
        return style;
    }

    void addChild(UIElement *child){
        if (child) {
            children.push_back(child);
            child->parent = this; // Set the parent of the child
        }
    }
    void removeChild(UIElement *child) {
        auto it = std::remove(children.begin(), children.end(), child);
        if (it != children.end()) {
            children.erase(it);
        }
    }
    std::vector<UIElement *> getChildren() const {
        return children;
    }
    void setParent(UIElement *parentElement) {
        parent = parentElement;
    }
};
