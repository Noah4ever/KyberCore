#include "components/audio/ESP32SDCardAudioPlayer.hpp"
#include "components/sdcard/SDCardIO.hpp"
#include "AudioGeneratorMP3.h"
#include "AudioFileSourceSD.h"
#include "AudioOutputI2S.h"
#include "AudioGeneratorWAV.h" // Add WAV generator
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

void ESP32SDCardAudioPlayer::setup()  {
    audioOutput = new AudioOutputI2S();
    audioOutput->SetPinout(I2S_BCLK_PIN, I2S_LRC_PIN, I2S_DIN_PIN);
    audioOutput->SetGain(static_cast<float>(currentVolume) / 100.0f); // Normalize volume to 0.0-1.0
}

void ESP32SDCardAudioPlayer::update()  {
    if (mp3Generator && mp3Generator->isRunning()) {
        if (!mp3Generator->loop()) {
            stop(); // Stop when MP3 playback finishes
        }
    }
    if (wavGenerator && wavGenerator->isRunning()) {
        if (!wavGenerator->loop()) {
            stop(); // Stop when WAV playback finishes
        }
    }
}


static bool endsWith(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

void ESP32SDCardAudioPlayer::play(const std::string& filename) {
    stop(); // Stop any currently playing audio

    if (sdCardIO && sdCardIO->exists(filename)) {
        Serial.printf("Playing file: %s\n", filename.c_str());
        if (endsWith(filename.c_str(), ".mp3") || endsWith(filename.c_str(), ".MP3")) {
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
                Serial.printf("Error opening MP3 file: %s\n", filename.c_str());
                cleanupAudioObjects();
            }
        }  else if (endsWith(filename.c_str(), ".wav") || endsWith(filename.c_str(), ".WAV")) {
            wavFileSource = new AudioFileSourceSD(filename.c_str());
            if (wavFileSource->isOpen()) {
                wavGenerator = new AudioGeneratorWAV();
                if (wavGenerator->begin(wavFileSource, audioOutput)) {
                    isCurrentlyPlaying = true;
                } else {
                    Serial.println("Error starting WAV generator.");
                    cleanupAudioObjects();
                }
            } else {
                Serial.printf("Error opening WAV file: %s\n", filename.c_str());
                cleanupAudioObjects();
            }
        } else {
            Serial.println("Unsupported audio format.");
        }
    } else {
        Serial.printf("File not found: %s\n", filename.c_str());
    }
}

void ESP32SDCardAudioPlayer::pause() {
    if (mp3Generator && mp3Generator->isRunning()) {
        // mp3Generator->pause(); // Check if pause is reliably implemented for MP3
        isCurrentlyPlaying = false;
    }
    if (wavGenerator && wavGenerator->isRunning()) {
        // wavGenerator->pause(); // Check if pause is reliably implemented for WAV
        isCurrentlyPlaying = false;
    }
}

void ESP32SDCardAudioPlayer::stop() {
    if (mp3Generator) {
        mp3Generator->stop();
    }
    if (wavGenerator) {
        wavGenerator->stop();
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
    if (wavGenerator) {
        delete wavGenerator;
        wavGenerator = nullptr;
    }
    if (wavFileSource) {
        delete wavFileSource;
        wavFileSource = nullptr;
    }
}
