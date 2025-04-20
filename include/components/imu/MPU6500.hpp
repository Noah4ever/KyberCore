/**
 * @file MPU6500.hpp
 * @brief Declaration of the MPU6500 IMU sensor wrapper implementing IComponent
 * @author Noah Thiering
 * @date 2025-04-18
 * @version 1.0
 *
 * This file defines the MPU6500 class which encapsulates
 * the MPU9250_WE library and provides the IComponent interface
 * for initialization, updates, and calibration.
 */

#pragma once

#include "components/imu/IMUSensor.hpp" 

#include <ArduinoJson.h>
#include <memory>

class MPU6500 : public IMUSensor {
public:
     MPU6500(const ArduinoJson::JsonObjectConst& config);
    ~MPU6500() override; // Destructor

    // Interface implementations
    void setup() override;
    void update() override;
    Vector3D getOrientation() const override;
    Vector3D getAcceleration() const override;
    Vector3D getGyroscope() const override;
    void calibrate(const ArduinoJson::JsonObjectConst& config) override;
    bool isCalibrated() const override;
    float getTemperature() const override;
    void setUpdateFrequency(float frequency) override;
    ErrorCode getLastError() const override;

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
};
