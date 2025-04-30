#pragma once

#include <cstdint>
#include <vector>

enum class EventType {
    NONE,

    STATE_CHANGED,

    IMU_DATA_CHANGED,

    BRIGHTNESS_CHANGED,

    VOLUME_CHANGED,

    INIT_COLOR_CHANGED,
    COLOR_CHANGED,

    GENERIC_PUSH_BUTTON_PRESSED,
    GENERIC_PUSH_BUTTON_RELEASED,
    GENERIC_PUSH_BUTTON_CLICKED,
    GENERIC_PUSH_BUTTON_LONG_PRESSED,
    GENERIC_PUSH_BUTTON_DOUBLE_CLICKED,

    DISPLAY_REQUEST_UPDATE,

    AUDIO_PLAY_TRACK,
    AUDIO_PAUSE,
    AUDIO_STOP,
    AUDIO_SET_VOLUME,
    AUDIO_NEXT,
    AUDIO_PREVIOUS,

    ANIMATION_REQUESTED, // maybe dont need this

    RAW_ROTARY_ROTATION_CHANGED,
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
    BLADE_RAINBOW_ANIMATION,
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
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct Vector3D {
    float x;
    float y;
    float z;
};

struct IMUData {
    Vector3D accel;
    Vector3D gyro;
    Vector3D mag;
};