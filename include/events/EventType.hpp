#pragma once

enum class EventType {
    NONE,

    IMU_DATA_CHANGED,

    BRIGHTNESS_CHANGED,

    VOLUME_CHANGED,

    COLOR_CHANGED,

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
    VOLUME_LEVEL, 
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

struct VolumeData {
    float level;
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