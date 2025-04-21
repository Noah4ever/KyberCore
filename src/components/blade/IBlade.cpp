#include "components/blade/IBlade.hpp"
#include "events/EventType.hpp"

void IBlade::addAnimation(EventType type, std::unique_ptr<IAnimation> animation) {
    animations[type] = std::move(animation);
}

void IBlade::playAnimation(EventType animationType, const ArduinoJson::JsonObjectConst& config) {
    stopAnimation();

    auto it = animations.find(animationType);
    if (it != animations.end()) {
        currentAnimation = it->second.get();
        currentAnimationConfig = config;
        currentAnimation->play(this, config);
    }
}

void IBlade::updateAnimation() {
    if (currentAnimation && currentAnimation->isPlaying()) {
        currentAnimation->update(this);
    }
}

bool IBlade::isAnimationPlaying() const {
    return currentAnimation && currentAnimation->isPlaying();
}

void IBlade::stopAnimation() {
    if (currentAnimation) {
        currentAnimation->stop();
        currentAnimation = nullptr;
    }
}

void IBlade::handleEvent(const Event& event) {
    switch (event.type) {
        case EventType::COLOR_CHANGED:
            if (event.dataType == DataType::COLOR_VALUE) {
                setColor(event.colorData);
            }
            break;
        case EventType::BRIGHTNESS_CHANGED:
            if (event.dataType == DataType::INT) {
                setBrightness(event.intData.value);
            }
            break;
        case EventType::BLADE_IGNITE:
            if (event.dataType == DataType::JSON_OBJECT) {
                playAnimation(EventType::BLADE_IGNITE, event.jsonData.as<ArduinoJson::JsonObjectConst>());
            } else {
                playAnimation(EventType::BLADE_IGNITE); 
            }
            break;
        case EventType::BLADE_EXTINGUISH:
            if (event.dataType == DataType::JSON_OBJECT) {
                playAnimation(EventType::BLADE_EXTINGUISH, event.jsonData.as<ArduinoJson::JsonObjectConst>());
            } else {
                playAnimation(EventType::BLADE_EXTINGUISH); 
            }
            break;
        case EventType::BLADE_BLASTER_REFLECT:
            if (event.dataType == DataType::JSON_OBJECT) {
                playAnimation(EventType::BLADE_BLASTER_REFLECT, event.jsonData.as<ArduinoJson::JsonObjectConst>());
            } else {
                playAnimation(EventType::BLADE_BLASTER_REFLECT); 
            }
            break;
        default:
            break;
    }
}