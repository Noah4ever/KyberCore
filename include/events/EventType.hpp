#pragma once

enum class EventType {
    NONE,
    IMU_DATA_CHANGED,
    VOLUME_CHANGED,
    COLOR_CHANGED,
    ANIMATION_REQUESTED,
    ROTARY_ROTATION_CHANGED,
    ROTARY_BUTTON_PRESSED,

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
    std::string value; // Can lead to memory issues if not managed properly because of deconstructor i think TODO: Fix
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