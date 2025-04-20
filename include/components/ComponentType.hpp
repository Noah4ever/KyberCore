#pragma once

enum MainComponentType
{
    MAIN_COMPONENT_TYPE_NONE = 0,
    BLADE,
    IMU,
    ROTARY_ENCODER,
};

enum ComponentType
{
    UNKNOWN = 0,
    ROTARY_ENCODER_GENERIC,
    IMU_MPU6500,
    BLADE_NEOPIXEL,
    BLADE_SINGLE_LED,
};