/**
 * @file MPU9250.hpp
 * @brief Declaration of the MPU9250 IMU sensor wrapper implementing IComponent
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

class MPU9250 : public IMUSensor {
public:
     MPU9250(const ArduinoJson::JsonObjectConst& config);
    ~MPU9250() override; // Destructor

    // Interface implementations
    void setup() override;
    void update() override;
    Vector3D getOrientation() const override;
    Vector3D getAcceleration() const override;
    Vector3D getGyroscope() const override;
    Vector3D getMagnetometer() const;
    void calibrate(const ArduinoJson::JsonObjectConst& config) override;
    bool isCalibrated() const override;
    float getTemperature() const override;
    void setUpdateFrequency(float frequency) override;
    ErrorCode getLastError() const override;

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
};
