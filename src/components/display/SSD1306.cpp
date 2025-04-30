/**
 * @file SSD1306.cpp
 * @brief Implementation of the SSD1306 OLED display wrapper implementing IDisplay
 * @author Noah Thiering
 * @date 2025-04-22
 * @version 1.0
 *
 * This file implements the SSD1306 class using the Adafruit_SSD1306 library.
 */
#include "components/display/SSD1306.hpp"
#include <ArduinoJson.h>
#include <memory>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <string>
#include <core/ComponentRegistrar.hpp>

struct SSD1306::Impl {
    int address;
    int width;
    int height;
    Adafruit_SSD1306 display;

    Impl(int addr, int w, int h, int reset) : address(addr), width(w), height(h), display(w, h, &Wire, reset) {}
};

SSD1306::SSD1306(const ArduinoJson::JsonObjectConst& config) : IDisplay(), pimpl_(std::make_unique<Impl>(
    0x3C,
    128,
    32,
    34
)) {}

SSD1306::~SSD1306() {
}

void SSD1306::setup() {
    if (!pimpl_->display.begin(SSD1306_SWITCHCAPVCC, pimpl_->address)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (1);
    }
    pimpl_->display.clearDisplay();
    pimpl_->display.setTextColor(SSD1306_WHITE);
    pimpl_->display.setTextSize(1);
    pimpl_->display.setCursor(0, 0);
    pimpl_->display.display();

}

void SSD1306::update() {}

void SSD1306::drawRect(int x, int y, int width, int height) {
    pimpl_->display.drawRect(x, y, width, height, SSD1306_WHITE);
}

void SSD1306::drawRect(int x, int y, int width, int height, int radius) {
    pimpl_->display.drawRoundRect(x, y, width, height, radius, SSD1306_WHITE);
}

void SSD1306::drawFillRect(int x, int y, int width, int height) {
    pimpl_->display.fillRect(x, y, width, height, SSD1306_WHITE);
}

void SSD1306::drawFillRect(int x, int y, int width, int height, int radius) {
    pimpl_->display.fillRoundRect(x, y, width, height, radius, SSD1306_WHITE);
}

void SSD1306::drawFillRect(int x, int y, int width, int height, UIColor color) {
    pimpl_->display.fillRoundRect(x, y, width, height, 0, static_cast<int>(color));
}

void SSD1306::clearDisplayInternal() {
    pimpl_->display.clearDisplay();
}

void SSD1306::drawIconInternal(int x, int y, const uint8_t *icon, int width, int height) {
    pimpl_->display.drawBitmap(x, y, icon, width, height, SSD1306_WHITE);
}

void SSD1306::drawProgressBarInternal(int x, int y, int width, int height, int progress) {
    pimpl_->display.drawRoundRect(x, y, width, height, 4, SSD1306_WHITE);
    int barWidth = (progress * (width - 2)) / 100;
    pimpl_->display.fillRoundRect(x, y + 1, barWidth, height - 2, 4, SSD1306_WHITE);
}

void SSD1306::drawValueInternal(int x, int y, int value) {
    pimpl_->display.setCursor(x, y);
    pimpl_->display.print(value);
}

void SSD1306::drawTextInternal(int x, int y, const std::string &text) {
    pimpl_->display.setCursor(x, y);
    pimpl_->display.print(text.c_str());
}

void SSD1306::drawTextInternal(int x, int y, const std::string &text, uint8_t textSize) {
    pimpl_->display.setTextSize(textSize);
    pimpl_->display.setCursor(x, y);
    pimpl_->display.print(text.c_str());
}

void SSD1306::drawValueInternal(int x, int y, int value, uint8_t textSize) {
    pimpl_->display.setTextSize(textSize);
    pimpl_->display.setCursor(x, y);
    pimpl_->display.print(value);
}

void SSD1306::displayInternal() {
    pimpl_->display.display();
}



static ComponentRegistrar<ComponentType::DISPLAY_SSD1306> registrar("ssd1306",
    [](const ArduinoJson::JsonObjectConst& config) -> IComponent* {
        return new SSD1306(config);
    }
);
