/**
 * @file UIBuilder.hpp
 * @brief Builder class for constructing display UI elements.
 * @author Noah Thiering
 * @date 2025-04-22
 * @version 1.0
 *
 * This class provides a fluent interface for building a collection
 * of displayable UI elements (progress bars, icons, text, etc.).
 */
#pragma once

#include <string>
#include <vector>

struct UIElement {
    enum class Type {
        PROGRESS_BAR,
        ICON,
        TEXT,
        VALUE // Separate for numerical values
    };
    Type type;
    int x = 0;
    int y = 0;

    // Progress Bar Data
    int progressBarWidth = 0;
    int progressBarHeight = 0;
    int progressBarValue = 0;

    // Icon Data
    const uint8_t* iconData = nullptr;
    int iconWidth = 0;
    int iconHeight = 0;

    // Text/Value Data
    std::string text;
    int value = 0;
};

class UIBuilder {
public:
    UIBuilder();
    ~UIBuilder() = default;

    UIBuilder& addProgressBar(int x, int y, int width, int height, int value);
    UIBuilder& addIcon(int x, int y, const uint8_t* data, int width, int height);
    UIBuilder& addText(int x, int y, const std::string& text);
    UIBuilder& addValue(int x, int y, int value);

    std::vector<UIElement> build();
    void clear();

private:
    std::vector<UIElement> elements;
};