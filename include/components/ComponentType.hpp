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
    DISPLAY_SSD1306,
    AUDIO_DFPLAYER_MINI,
    BLADE_NEOPIXEL,
    BLADE_SINGLE_LED,
};