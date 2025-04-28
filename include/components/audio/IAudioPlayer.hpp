/**
 * @file IAudioPlayer.hpp
 * @brief Interface for audio player components.
 * @author Noah Thiering
 * @date 2025-04-22
 * @version 1.1 (Updated for SD card playback)
 *
 * Defines the interface for audio player components that play
 * audio files from an SD card.
 */
#pragma once

#include "components/IComponent.hpp"
#include <string>

class IAudioPlayer : public IComponent
{
public:
    void setup() override;
    void update() override;

    virtual ~IAudioPlayer() = default;

    /**
     * @brief Starts playing the audio file from the SD card.
     *
     * @param filename The full path to the audio file on the SD card (e.g., "/audio/track.mp3").
     */
    virtual void play(const std::string &filename) = 0;

    /**
     * @brief Pauses the currently playing audio.
     */
    virtual void pause() = 0;

    /**
     * @brief Stops the currently playing audio.
     */
    virtual void stop() = 0;

    /**
     * @brief Sets the playback volume.
     *
     * @param volume The volume level (e.g., 0-100, or a normalized range like 0.0-1.0 - define in implementation).
     */
    virtual void setVolume(int volume) = 0;

    /**
     * @brief Gets the current playback volume.
     *
     * @return The current volume level.
     */
    virtual int getVolume() const = 0;

    /**
     * @brief Checks if audio is currently playing.
     *
     * @return true if playing, false otherwise.
     */
    virtual bool isPlaying() const = 0;
};