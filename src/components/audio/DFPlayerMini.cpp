#include "components/audio/DFPlayerMini.hpp"
#include "events/EventBus.hpp"
#include "events/EventType.hpp"
#include <ArduinoJson.h>
#include <memory>
#include <DFRobotDFPlayerMini.h>
#include <HardwareSerial.h>
#include <core/ComponentRegistrar.hpp>

#define FPSerial Serial1

struct DFPlayerMini::Impl {
    DFRobotDFPlayerMini player;
    HardwareSerial* hardSerial = nullptr;
    bool useSoftwareSerial;
    int rxPin;
    int txPin;
    bool isPlayingTrack = false;
    int currentVolume = 15; // Default volume
};

DFPlayerMini::DFPlayerMini(const ArduinoJson::JsonObjectConst& config) : pimpl_(std::make_unique<Impl>()) {
    // pimpl_->useSoftwareSerial = config["use_soft_serial"] | true; // Default to soft serial
    pimpl_->rxPin = config["rx_pin"] | 3;                       // Default RX pin
    pimpl_->txPin = config["tx_pin"] | 1;                       // Default TX pin

    delay(3000); // Allow time for the system to stabilize
    Serial.println(F("1111Initializing DFPlayerMini ...")); // ???? AFTER THIS NOT WORKING
    delay(1000);
    FPSerial.begin(9600, SERIAL_8N1, 1, 3);

    delay(3000); // Allow time for the system to stabilize
    Serial.println("2222Initializing DFPlayerMini ...");
    delay(1000);

}

DFPlayerMini::~DFPlayerMini() {
}

void DFPlayerMini::setup() {
    delay(3000); // Allow time for the system to stabilize
    Serial.println(F("33333nitializing DFPlayerMini ..."));
    delay(1000);
    Serial.println("Serial1 initialized.");
    delay(2000);
    Serial.println(F("Initializing DFPlayerMini ... (May take 3~5 seconds)"));
    delay(3000);
    if (!pimpl_->player.begin(FPSerial, true, true)) {
        Serial.println(F("Error initializing DFPlayerMini (Serial1 ESP32). Check connections."));
    } else {
        Serial.println(F("DFPlayerMini initialized via Serial1."));
    }
    Serial.println("DFPlayer Mini online.");

    pimpl_->player.volume(pimpl_->currentVolume);

    EventBus::getInstance().subscribe(this, EventType::VOLUME_CHANGED);

    EventBus::getInstance().subscribe(this, EventType::AUDIO_PLAY_TRACK);
    EventBus::getInstance().subscribe(this, EventType::AUDIO_PAUSE);
    EventBus::getInstance().subscribe(this, EventType::AUDIO_STOP);
    EventBus::getInstance().subscribe(this, EventType::AUDIO_SET_VOLUME);
    EventBus::getInstance().subscribe(this, EventType::AUDIO_NEXT);
    EventBus::getInstance().subscribe(this, EventType::AUDIO_PREVIOUS);
}

void DFPlayerMini::update() {
    // print all file count on the sd card
    if (pimpl_->player.available()) {
        int fileCount = pimpl_->player.readFileCounts();
        Serial.print(F("File Count: "));
        Serial.println(fileCount);
    }else{
        Serial.println(F("No files found on the SD card."));
    }
    handleDFPlayerEvents();
}

void DFPlayerMini::play(int trackNumber) {
    pimpl_->player.play(trackNumber);
    pimpl_->isPlayingTrack = true;
}

void DFPlayerMini::pause() {
    pimpl_->player.pause();
    pimpl_->isPlayingTrack = false;
}

void DFPlayerMini::stop() {
    pimpl_->player.stop();
    pimpl_->isPlayingTrack = false;
}

void DFPlayerMini::setVolume(int volume) {
    if (volume >= 0 && volume <= 30) {
        pimpl_->player.volume(volume);
        pimpl_->currentVolume = volume;
    }
}

int DFPlayerMini::getVolume() const {
    return pimpl_->currentVolume;
}

bool DFPlayerMini::isPlaying() const {
    return pimpl_->isPlayingTrack; // Basic tracking, might need improvement
}

void DFPlayerMini::next() {
    pimpl_->player.next();
}

void DFPlayerMini::previous() {
    pimpl_->player.previous();
}

void DFPlayerMini::handleEvent(const Event& event) {
    switch (event.type) {
        case EventType::VOLUME_CHANGED:
            if (event.dataType == DataType::INT) {
                setVolume(event.intData.value);
            }
            break;
        case EventType::AUDIO_PLAY_TRACK:
            if (event.dataType == DataType::INT) {
                play(event.intData.value);
            }
            break;
        case EventType::AUDIO_PAUSE:
            pause();
            break;
        case EventType::AUDIO_STOP:
            stop();
            break;
        case EventType::AUDIO_SET_VOLUME:
            if (event.dataType == DataType::INT) {
                setVolume(event.intData.value);
            }
            break;
        case EventType::AUDIO_NEXT:
            next();
            break;
        case EventType::AUDIO_PREVIOUS:
            previous();
            break;
        default:
            break;
    }
}

void DFPlayerMini::handleDFPlayerEvents() {
    if (pimpl_->player.available()) {
        printDFPlayerDetail(pimpl_->player.readType(), pimpl_->player.read());
    }
}

void DFPlayerMini::printDFPlayerDetail(uint8_t type, int value) {
    switch (type) {
        case TimeOut:
            Serial.println(F("DFPlayer Timeout!"));
            break;
        case WrongStack:
            Serial.println(F("DFPlayer Stack Wrong!"));
            break;
        case DFPlayerCardInserted:
            Serial.println(F("DFPlayer Card Inserted!"));
            break;
        case DFPlayerCardRemoved:
            Serial.println(F("DFPlayer Card Removed!"));
            break;
        case DFPlayerCardOnline:
            Serial.println(F("DFPlayer Card Online!"));
            break;
        case DFPlayerUSBInserted:
            Serial.println(F("DFPlayer USB Inserted!"));
            break;
        case DFPlayerUSBRemoved:
            Serial.println(F("DFPlayer USB Removed!"));
            break;
        case DFPlayerPlayFinished:
            Serial.print(F("DFPlayer Play Finished, Track: "));
            Serial.println(value);
            pimpl_->isPlayingTrack = false;
            break;
        case DFPlayerError:
            Serial.print(F("DFPlayer Error: "));
            switch (value) {
                case Busy:
                    Serial.println(F("Card not found"));
                    break;
                case Sleeping:
                    Serial.println(F("Sleeping"));
                    break;
                case SerialWrongStack:
                    Serial.println(F("Get Wrong Stack"));
                    break;
                case CheckSumNotMatch:
                    Serial.println(F("Check Sum Not Match"));
                    break;
                case FileIndexOut:
                    Serial.println(F("File Index Out of Bound"));
                    break;
                case FileMismatch:
                    Serial.println(F("Cannot Find File"));
                    break;
                case Advertise:
                    Serial.println(F("In Advertise"));
                    break;
                default:
                    Serial.print(F("Unknown Error: "));
                    Serial.println(value);
                    break;
            }
            break;
        default:
            break;
    }
}


static ComponentRegistrar<ComponentType::AUDIO_DFPLAYER_MINI> registrar("dfplayer_mini",
    [](const ArduinoJson::JsonObjectConst& config) -> IComponent* {
        return new DFPlayerMini(config);
    }
);