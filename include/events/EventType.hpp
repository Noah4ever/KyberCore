#pragma once

#include "ui/UIBuilder.hpp"

#include <cstdint>
#include <vector>

enum class EventType {
    NONE,

    IMU_DATA_CHANGED,

    BRIGHTNESS_CHANGED,

    VOLUME_CHANGED,

    COLOR_CHANGED,

    DISPLAY_CLEAR_REQUESTED,
    DISPLAY_TEXT_REQUESTED,
    DISPLAY_PROGRESS_REQUESTED,
    DISPLAY_ICON_REQUESTED,
    DISPLAY_UI_REQUESTED,

    AUDIO_PLAY_TRACK,
    AUDIO_PAUSE,
    AUDIO_STOP,
    AUDIO_SET_VOLUME,
    AUDIO_NEXT,
    AUDIO_PREVIOUS,

    ANIMATION_REQUESTED, // maybe dont need this

    ROTARY_ROTATION_CHANGED,
    ROTARY_BUTTON_PRESSED,
    ROTARY_BUTTON_LONG_PRESSED,
    ROTARY_BUTTON_DOUBLE_CLICKED,
    ROTARY_BUTTON_CLICKED,
    ROTARY_BUTTON_RELEASED,

    BLADE_IGNITE,
    BLADE_EXTINGUISH,
    BLADE_BLASTER_REFLECT,
    BLADE_BLADE_LOCK,
};

enum class DataType {
    NONE,
    INT,
    FLOAT,
    BOOL,
    STRING,
    COLOR_VALUE,
    VECTOR3D,
    IMUDATA,
    JSON_OBJECT,
    DISPLAY_UI_DATA,
};
    
struct IntData {
    int value;
};

struct FloatData {
    float value;
};

struct BoolData {
    bool value;
};

struct StringData {
    char value[256]; // Changed from std::string to char array to avoid memory issues
    
};

struct ColorData {
    int red;
    int green;
    int blue;
};

struct Vector3D {
    float x;
    float y;
    float z;
};

struct IMUData {
    Vector3D accel;
    Vector3D gyro;
};

struct DisplayUIData {
    std::vector<UIElement> elements;
};