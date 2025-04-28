#pragma once

#include "components/IComponent.hpp"
#include "components/blade/BladeType.hpp"
#include "events/EventType.hpp"
#include "events/IEventListener.hpp"
#include "components/blade/animations/IAnimation.hpp"  
#include "states/ColorState.hpp"

#include <ArduinoJson.h>
#include <memory>
#include <FastLED.h>
#include <map>

class IAnimation; // Forward declaration

class IBlade : public IComponent, public IEventListener
{
    public:
    virtual ~IBlade() = default;
    virtual void setup() = 0;
    virtual void show() = 0;

    virtual void setInitColor(ColorData color) = 0;
    virtual void setColor(ColorData color, bool force = false) = 0;
    virtual ColorData getColor() const = 0;
    virtual void setBrightness(int brightness, bool force = false) = 0;

    virtual BladeType getType() const = 0;
    virtual void playAnimation(EventType animationType, const ArduinoJson::JsonObjectConst& config = ArduinoJson::JsonObjectConst());
    virtual void updateAnimation();
    virtual bool isAnimationPlaying() const;
    virtual void stopAnimation();

    virtual void handleEvent(const Event& event) override;

protected:
    bool bladeIsIgnited = false;
    std::map<EventType, std::unique_ptr<IAnimation>> animations;
    IAnimation* currentAnimation = nullptr;
    ArduinoJson::JsonObjectConst currentAnimationConfig;

    void addAnimation(EventType type, std::unique_ptr<IAnimation> animation);

public:
};