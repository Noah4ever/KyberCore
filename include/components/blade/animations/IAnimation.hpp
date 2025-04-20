#pragma once

#include "components/blade/IBlade.hpp"
#include <ArduinoJson.h>

class IAnimation {
public:
    virtual ~IAnimation() = default;
    virtual void play(IBlade* blade, unsigned long duration, const ArduinoJson::JsonObjectConst& config = ArduinoJson::JsonObjectConst()) = 0;
    virtual void update(IBlade* blade) = 0;
    virtual bool isPlaying() const = 0;
    virtual void stop() = 0;
};
