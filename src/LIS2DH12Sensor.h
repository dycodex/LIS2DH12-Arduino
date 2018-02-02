#ifndef __LIS2DH12_SENSOR_H__
#define __LIS2DH12_SENSOR_H__

#include <Arduino.h>
#include <Wire.h>
#include "LIS2DH12_Driver.h"

typedef enum {
    LIS2DH12_STATUS_OK = 0,
    LIS2DH12_STATUS_ERROR,
    LIS2DH12_STATUS_TIMEOUT,
    LIS2DH12_STATUS_NOT_IMPLEMENTED,
} LIS2DH12StatusType;

typedef enum {
    LIS2DH12_MODE_HIGH_RESOLUTION = 0,
    LIS2DH12_MODE_LOW_POWER,
    LIS2DH12_MODE_NORMAL,
} LIS2DH12OperatingMode;

class LIS2DH12Sensor {
public:
    LIS2DH12Sensor(TwoWire *i2c);
    LIS2DH12Sensor(TwoWire *i2c, uint8_t address);

    LIS2DH12StatusType begin();
    LIS2DH12StatusType setOdr(LIS2DH12_ODR_t odr);
    LIS2DH12StatusType getOdr(LIS2DH12_ODR_t *odr);
    LIS2DH12StatusType enableAxes();
    LIS2DH12StatusType disableAxes();
    LIS2DH12StatusType enableLowPower();
    LIS2DH12StatusType disableLowPower();
    LIS2DH12StatusType enableHighResolution();
    LIS2DH12StatusType disableHighResolution();
    LIS2DH12StatusType setFullScale(LIS2DH12_FS_t fullScale);
    LIS2DH12StatusType getFullScale(LIS2DH12_FS_t *fullScale);
    LIS2DH12StatusType getRawAxes(int16_t *axes);
    LIS2DH12StatusType getAxes(int16_t *axes);
    LIS2DH12StatusType readID(uint8_t *ID);

    uint8_t read(uint8_t *buffer, uint8_t registerAddr, uint16_t length) {
        int i = 0;
        
        i2c_->beginTransmission(address_);
        i2c_->write(registerAddr);
        i2c_->endTransmission(false);
        i2c_->requestFrom(address_, (byte)length);

        while (i2c_->available()) {
            buffer[i] = i2c_->read();
            i++;
        }

        return 0;
    }

    uint8_t write(uint8_t *buffer, uint8_t registerAddr, uint16_t length) {
        i2c_->beginTransmission(address_);
        i2c_->write(registerAddr);

        for (uint16_t i = 0; i < length; i++) {
            i2c_->write(buffer[i]);
        }

        i2c_->endTransmission();

        return 0;
    }

private:
    TwoWire *i2c_;
    uint8_t address_;
    LIS2DH12OperatingMode operatingMode_;
};

#ifdef __cplusplus
extern "C" {
#endif

uint8_t LIS2DH12_IO_Write(void *handle, uint8_t address, uint8_t *buffer, uint16_t length);
uint8_t LIS2DH12_IO_Read(void *handle, uint8_t address, uint8_t *buffer, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif
