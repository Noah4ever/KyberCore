#pragma once

#include "components/IComponent.hpp"
#include "events/EventType.hpp"
#include <ArduinoJson.h>

class IMUSensor : public IComponent {
public:

    // Common IMU interface methods
    virtual Vector3D getOrientation() const = 0;       // Roll, Pitch, Yaw in degrees
    virtual Vector3D getAcceleration() const = 0;      // X, Y, Z in m/s²
    virtual Vector3D getGyroscope() const = 0;         // X, Y, Z in rad/s
    virtual Vector3D getMagnetometer() { return Vector3D(); };      // X, Y, Z in uT (if applicable)
    
    // Configuration
    virtual void calibrate(const ArduinoJson::JsonObjectConst& config) = 0;
    virtual bool isCalibrated() const = 0;
    
    // Sensor-specific features
    virtual float getTemperature() const = 0;          // In Celsius
    
    // IMU-specific update cycle management
    virtual void setUpdateFrequency(float frequency) = 0;  // In Hz
    
    // Error handling
    enum class ErrorCode {
        NONE,
        IMU_COMMUNICATION_FAILURE,
        IMU_CALIBRATION_NEEDED,
        IMU_OVERFLOW
    };
    
    virtual ErrorCode getLastError() const = 0;
    
    // Factory method type for registration
    using Factory = IMUSensor*(*)(ArduinoJson::JsonObjectConst&);
    
protected:
    // Protected constructor to enforce abstract base class
    IMUSensor() = default;
    // Destructor
    virtual ~IMUSensor() = default;

private:
    // Prevent copying
    IMUSensor(const IMUSensor&) = delete;
    void operator=(const IMUSensor&) = delete;
};