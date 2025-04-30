#pragma once

#include "components/audio/IAudioPlayer.hpp"
#include "components/sdcard/SDCardIO.hpp"
#include <string>

// Forward declarations for ESP8266Audio library classes
class AudioGeneratorMP3;
class AudioFileSourceSD;
class AudioOutputI2S;
class AudioGeneratorWAV; // Add WAV generator

class ESP32SDCardAudioPlayer : public IAudioPlayer {
private:
    SDCardIO* sdCardIO;
    AudioGeneratorMP3* mp3Generator = nullptr;
    AudioFileSourceSD* mp3FileSource = nullptr;
    AudioGeneratorWAV* wavGenerator = nullptr; // Add WAV generator
    AudioFileSourceSD* wavFileSource = nullptr; // WAV also uses AudioFileSourceSD
    AudioOutputI2S* audioOutput = nullptr;
    bool isCurrentlyPlaying = false;
    int currentVolume = 15; // Default volume (adjust as needed)

    void cleanupAudioObjects();

public:
    ESP32SDCardAudioPlayer(SDCardIO* sdIO);
    ~ESP32SDCardAudioPlayer() override;

    void setup() override;
    void update() override;

    void play(const std::string& filename) override;
    void pause() override;
    void stop() override;
    void setVolume(int volume) override;
    int getVolume() const override;
    bool isPlaying() const override;
};