/**
 * @file MPU9250.cpp
 * @brief Declaration of the MPU9250 IMU sensor wrapper implementing IComponent
 * @author Noah Thiering
 * @date 2025-04-18
 * @version 1.0
 */

#include "components/imu/MPU9250.hpp"
#include "core/ComponentRegistry.hpp"
#include "components/ComponentType.hpp"
#include "core/ComponentRegistrar.hpp"
#include "events/EventBus.hpp"

#include <Wire.h>
#include <cstdint>        // for uint8_t
#include <MPU9250_WE.h>

/**
 * * @brief Implementation of the MPU9250 IMU sensor.
 * * This class provides methods to initialize, configure, and read data from the MPU9250 sensor.
 * * It uses the MPU9250_WE library for communication with the sensor.
 */
struct MPU9250::Impl { 
    explicit Impl(uint8_t addr)
    : sensor(addr) {}             // Constructor with I2C address for MPU9250_WE

    MPU9250_WE sensor;

    Vector3D accel_offset{0,0,0};
    Vector3D gyro_offset{0,0,0};
    Vector3D mag_offset{0,0,0};
    Vector3D last_accel{0,0,0};
    Vector3D last_gyro{0,0,0};
    Vector3D last_mag{0,0,0};
    float   update_frequency = 100.0f;
    ErrorCode last_error     = ErrorCode::NONE;
};

MPU9250::~MPU9250() = default; // Must appear AFTER Impl definition

MPU9250::MPU9250(const ArduinoJson::JsonObjectConst& config)
{
    // Get data from config
    const uint8_t i2c_addr = 0x68;
    const int     sda_pin  = config["imu"]["i2c_sda"]     | 21;
    const int     scl_pin  = config["imu"]["i2c_scl"]     | 22;

    // Initialize I2C communication
    Wire.begin(sda_pin, scl_pin);
    // Initialize the sensor with the specified I2C address
    pimpl_ = std::make_unique<Impl>(i2c_addr);
}

void MPU9250::setup()  
{
    if (!pimpl_->sensor.init()) {
        pimpl_->last_error = ErrorCode::IMU_COMMUNICATION_FAILURE;
        Serial.println("MPU9250 initialization failed");
        return;
    }

    if(!pimpl_->sensor.initMagnetometer()){
        Serial.println("Magnetometer does not respond");
      }
      else{
        Serial.println("Magnetometer is connected");
      }

    // Sensor configuration
    pimpl_->sensor.autoOffsets();
    pimpl_->sensor.enableGyrDLPF();
    pimpl_->sensor.setGyrDLPF(MPU9250_DLPF_6);
    pimpl_->sensor.setSampleRateDivider(5); // 1 kHz
    pimpl_->sensor.setGyrRange(MPU9250_GYRO_RANGE_250);
    pimpl_->sensor.setAccRange(MPU9250_ACC_RANGE_2G);
    pimpl_->sensor.enableAccDLPF(true);
    pimpl_->sensor.setAccDLPF(MPU9250_DLPF_6);
    pimpl_->sensor.setMagOpMode(AK8963_CONT_MODE_100HZ);

    setUpdateFrequency(pimpl_->update_frequency);
}

void MPU9250::update() {
    // Check for new data
    uint8_t status = pimpl_->sensor.readAndClearInterrupts();

    if (status == 0) {
        pimpl_->last_error = ErrorCode::NONE;
        return; // No new data
    }
    if (pimpl_->sensor.checkInterrupt(status, MPU9250_DATA_READY)) {
        auto accel = pimpl_->sensor.getGValues();
        auto gyro  = pimpl_->sensor.getGyrValues();
        auto mag   = pimpl_->sensor.getMagValues();
        
        auto resultantG = pimpl_->sensor.getResultantG(accel);

        pimpl_->last_accel = {
            accel.x - pimpl_->accel_offset.x,
            accel.y - pimpl_->accel_offset.y,
            accel.z - pimpl_->accel_offset.z
        };
        pimpl_->last_gyro = {
            gyro.x  - pimpl_->gyro_offset.x,
            gyro.y  - pimpl_->gyro_offset.y,
            gyro.z  - pimpl_->gyro_offset.z
        };
        
        pimpl_->last_mag = {
            mag.x  - pimpl_->mag_offset.x,
            mag.y  - pimpl_->mag_offset.y,
            mag.z  - pimpl_->mag_offset.z
        };

        // Publish IMU data event
        Event imu_data(EventType::IMU_DATA_CHANGED, DataType::IMUDATA);
        imu_data.imuData = { pimpl_->last_accel, pimpl_->last_gyro, pimpl_->last_mag };
        EventBus::getInstance().publish(imu_data);

        // read whoami
        uint8_t whoami = pimpl_->sensor.whoAmI();
        Serial.print("Who am I: ");
        Serial.println(whoami, HEX);

        // print all values
        // Serial.print("Accel: ");
        // Serial.print(pimpl_->last_accel.x);
        // Serial.print(", ");
        // Serial.print(pimpl_->last_accel.y);
        // Serial.print(", ");
        // Serial.print(pimpl_->last_accel.z);
        // Serial.print(" | Resultant G: ");
        // Serial.print(resultantG);
        // Serial.print(" | Gyro: ");
        // Serial.print(pimpl_->last_gyro.x);
        // Serial.print(", ");
        // Serial.print(pimpl_->last_gyro.y);
        // Serial.print(", ");
        // Serial.print(pimpl_->last_gyro.z);
        // Serial.print(" | Mag: ");
        // Serial.print(pimpl_->last_mag.x);
        // Serial.print(", ");
        // Serial.print(pimpl_->last_mag.y);
        // Serial.print(", ");
        // Serial.print(pimpl_->last_mag.z);
        // Serial.println();
    }
}


void MPU9250::calibrate(const ArduinoJson::JsonObjectConst& config)
{
    // Read calibration data from the config
    // This is a placeholder; actual calibration logic would depend on the specific sensor
    // and the calibration method used.
    pimpl_->accel_offset.x = config["accel_offset_x"] | 0.0f;
    pimpl_->accel_offset.y = config["accel_offset_y"] | 0.0f;
    pimpl_->accel_offset.z = config["accel_offset_z"] | 0.0f;
    pimpl_->gyro_offset.x  = config["gyro_offset_x"]  | 0.0f;
    pimpl_->gyro_offset.y  = config["gyro_offset_y"]  | 0.0f;
    pimpl_->gyro_offset.z  = config["gyro_offset_z"]  | 0.0f;
    pimpl_->mag_offset.x   = config["mag_offset_x"]   | 0.0f;
    pimpl_->mag_offset.y   = config["mag_offset_y"]   | 0.0f;
    pimpl_->mag_offset.z   = config["mag_offset_z"]   | 0.0f;
    
}

bool MPU9250::isCalibrated() const
{
    // Check if offsets are set to non-zero values
    // This is a simple check; in a real application, you might want to
    // implement a more sophisticated calibration check
    return (pimpl_->accel_offset.x != 0.0f ||
            pimpl_->accel_offset.y != 0.0f ||
            pimpl_->accel_offset.z != 0.0f) &&
           (pimpl_->gyro_offset.x  != 0.0f ||
            pimpl_->gyro_offset.y  != 0.0f ||
            pimpl_->gyro_offset.z  != 0.0f) &&
           (pimpl_->mag_offset.x   != 0.0f ||
            pimpl_->mag_offset.y   != 0.0f ||
            pimpl_->mag_offset.z   != 0.0f);
}

Vector3D MPU9250::getOrientation() const
{
    // Placeholder for orientation calculation
    return {0,0,0};
}

Vector3D MPU9250::getAcceleration() const
{
    return pimpl_->last_accel;
}

Vector3D MPU9250::getGyroscope() const
{
    return pimpl_->last_gyro;
}

Vector3D MPU9250::getMagnetometer() const
{
    return pimpl_->last_mag;
}

float MPU9250::getTemperature() const
{
    return pimpl_->sensor.getTemperature();
}

void MPU9250::setUpdateFrequency(float frequency)
{
    pimpl_->update_frequency = frequency;
    // Set the sample rate divider based on the desired frequency
    const uint16_t divider = static_cast<uint16_t>(1000.0f / frequency) - 1;
    pimpl_->sensor.setSampleRateDivider(divider);
}

IMUSensor::ErrorCode MPU9250::getLastError() const
{
    return pimpl_->last_error;
}

static ComponentRegistrar<ComponentType::IMU_MPU9250> registrar("mpu9250",
    [](const ArduinoJson::JsonObjectConst& config) -> IComponent* {
        return new MPU9250(config);
    }
);