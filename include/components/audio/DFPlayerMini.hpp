/**
 * @file DFPlayerMini.hpp
 * @brief Implementation of the DFPlayer Mini component using IAudioPlayer.
 * @author Noah Thiering
 * @date 2025-04-22
 * @version 1.0
 *
 * This class wraps the DFRobotDFPlayerMini library and implements
 * the IAudioPlayer interface, responding to audio-related events.
 */
#pragma once

#include "components/audio/IAudioPlayer.hpp"
#include "events/IEventListener.hpp"
#include "events/EventType.hpp"
#include <ArduinoJson.h>
#include <memory>

class DFPlayerMini : public IAudioPlayer, public IEventListener {
private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;

public:
    DFPlayerMini(const ArduinoJson::JsonObjectConst& config);
    ~DFPlayerMini() override;

    // IComponent interface
    void setup() override;
    void update() override;

    // IAudioPlayer interface
    void play(int trackNumber) override;
    void pause() override;
    void stop() override;
    void setVolume(int volume) override;
    int getVolume() const override;
    bool isPlaying() const override;
    void next() override;
    void previous() override;

    // IEventListener interface
    void handleEvent(const Event& event) override;

private:
    void handleDFPlayerEvents();
    void printDFPlayerDetail(uint8_t type, int value);
};