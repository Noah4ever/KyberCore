#include "components/audio/ESP32SDCardAudioPlayer.hpp"
#include "components/sdcard/SDCardIO.hpp"
#include "AudioGeneratorMP3.h"
#include "AudioFileSourceSD.h"
#include "AudioOutputI2S.h"
#include "Arduino.h"

// Define your I2S pinout here
#define I2S_BCLK_PIN 26
#define I2S_LRC_PIN 25
#define I2S_DIN_PIN 32

ESP32SDCardAudioPlayer::ESP32SDCardAudioPlayer(SDCardIO* sdIO) : sdCardIO(sdIO) {}

ESP32SDCardAudioPlayer::~ESP32SDCardAudioPlayer() {
    cleanupAudioObjects();
    if (audioOutput) delete audioOutput;
}

void ESP32SDCardAudioPlayer::setup() {
    audioOutput = new AudioOutputI2S();
    audioOutput->SetPinout(I2S_BCLK_PIN, I2S_LRC_PIN, I2S_DIN_PIN);
    audioOutput->SetGain(static_cast<float>(currentVolume) / 100.0f); // Normalize volume to 0.0-1.0
}

void ESP32SDCardAudioPlayer::update() {
    if (mp3Generator && mp3Generator->isRunning()) {
        if (!mp3Generator->loop()) {
            stop(); // Stop when playback finishes
        }
    }
}

void ESP32SDCardAudioPlayer::play(const std::string& filename) {
    stop(); // Stop any currently playing audio

    if (sdCardIO && sdCardIO->exists(filename)) {
        Serial.printf("Playing file: %s\n", filename.c_str());
        mp3FileSource = new AudioFileSourceSD(filename.c_str());
        if (mp3FileSource->isOpen()) {
            mp3Generator = new AudioGeneratorMP3();
            if (mp3Generator->begin(mp3FileSource, audioOutput)) {
                isCurrentlyPlaying = true;
            } else {
                Serial.println("Error starting MP3 generator.");
                cleanupAudioObjects();
            }
        } else {
            Serial.printf("Error opening file: %s\n", filename.c_str());
            cleanupAudioObjects();
        }
    } else {
        Serial.printf("File not found: %s\n", filename.c_str());
    }
}

void ESP32SDCardAudioPlayer::pause() {
    if (mp3Generator && mp3Generator->isRunning()) {
        // mp3Generator->pause();
        isCurrentlyPlaying = false; // Consider adding a 'isPaused' state if needed
    }
}

void ESP32SDCardAudioPlayer::stop() {
    if (mp3Generator) {
        mp3Generator->stop();
    }
    cleanupAudioObjects();
    isCurrentlyPlaying = false;
}

void ESP32SDCardAudioPlayer::setVolume(int volume) {
    currentVolume = constrain(volume, 0, 100); // Assuming 0-100 range
    if (audioOutput) {
        audioOutput->SetGain(static_cast<float>(currentVolume) / 100.0f);
    }
}

int ESP32SDCardAudioPlayer::getVolume() const {
    return currentVolume;
}

bool ESP32SDCardAudioPlayer::isPlaying() const {
    return isCurrentlyPlaying;
}

void ESP32SDCardAudioPlayer::cleanupAudioObjects() {
    if (mp3Generator) {
        delete mp3Generator;
        mp3Generator = nullptr;
    }
    if (mp3FileSource) {
        delete mp3FileSource;
        mp3FileSource = nullptr;
    }
}