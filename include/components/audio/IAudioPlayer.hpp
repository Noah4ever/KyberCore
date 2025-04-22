
/**
 * @file IAudioPlayer.hpp
 * @brief Interface for audio player components.
 * @author Noah Thiering
 * @date 2025-04-22
 * @version 1.0
 *
 * Defines the interface for audio player components, allowing
 * for basic audio control operations.
 */
#pragma once

#include "components/IComponent.hpp"
#include <string>

class IAudioPlayer : public IComponent {
public:
    virtual ~IAudioPlayer() = default;

    virtual void play(int trackNumber) = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void setVolume(int volume) = 0; // Volume level (e.g., 0-30)
    virtual int getVolume() const = 0;
    virtual bool isPlaying() const = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
};