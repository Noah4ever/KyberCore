/**
 * @file SSD1306.hpp
 * @brief Declaration of the SSD1306 OLED display wrapper implementing IDisplay
 * @author Noah Thiering
 * @date 2025-04-22
 * @version 1.0
 *
 * This file defines the SSD1306 class which encapsulates
 * the Adafruit_SSD1306 library and provides the IDisplay interface
 * for initialization and display functionalities.
 */
#pragma once

#include "components/display/IDisplay.hpp"
#include <ArduinoJson.h>
#include <string>
#include <memory>

class SSD1306 : public IDisplay {
public:
    SSD1306(const ArduinoJson::JsonObjectConst& config);
    ~SSD1306() override;

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;

    void clearDisplayInternal() override;
    void drawIconInternal(int x, int y, const uint8_t *icon, int width, int height) override;
    void drawProgressBarInternal(int x, int y, int width, int height, int progress) override;
    void drawValueInternal(int x, int y, int value) override;
    void drawValueInternal(int x, int y, int value, uint8_t textSize) override;
    void drawTextInternal(int x, int y, const std::string &text) override;
    void drawTextInternal(int x, int y, const std::string &text, uint8_t textSize) override;
    void displayInternal() override;

public:
    void setup() override;
    void update() override;
};