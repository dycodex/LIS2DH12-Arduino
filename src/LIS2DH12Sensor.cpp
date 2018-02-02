#include "LIS2DH12Sensor.h"

LIS2DH12Sensor::LIS2DH12Sensor(TwoWire *i2c):
 i2c_(i2c), address_(LIS2DH12_I2C_ADDRESS) {}

LIS2DH12Sensor::LIS2DH12Sensor(TwoWire *i2c, uint8_t address):
 i2c_(i2c), address_(address) {}

LIS2DH12StatusType LIS2DH12Sensor::begin() {
    i2c_->begin();

    operatingMode_ = LIS2DH12_MODE_NORMAL;

    if (setOdr(LIS2DH12_ODR_200Hz) == LIS2DH12_STATUS_ERROR) {
        return LIS2DH12_STATUS_ERROR;
    }

    if (enableAxes() == LIS2DH12_STATUS_ERROR) {
        return LIS2DH12_STATUS_ERROR;
    }

    if (setFullScale(LIS2DH12_FS_2g) == LIS2DH12_STATUS_ERROR) {
        return LIS2DH12_STATUS_ERROR;
    }

    return LIS2DH12_STATUS_OK;
}

LIS2DH12StatusType LIS2DH12Sensor::setOdr(LIS2DH12_ODR_t odr) {
    if (LIS2DH12_Write_ODR((void*)this, odr)) {
        return LIS2DH12_STATUS_OK;
    }

     return LIS2DH12_STATUS_ERROR;
}

LIS2DH12StatusType LIS2DH12Sensor::enableAxes() {
    if (LIS2DH12_Enable_Axes((void*)this, (LIS2DH12_AxesEnable_t)(LIS2DH12_ENABLE_X|LIS2DH12_ENABLE_Y|LIS2DH12_ENABLE_Z))) {
        return LIS2DH12_STATUS_OK;
    }

     return LIS2DH12_STATUS_ERROR;
}

LIS2DH12StatusType LIS2DH12Sensor::disableAxes() {
    if (LIS2DH12_Disable_Axes((void*)this)) {
        return LIS2DH12_STATUS_OK;
    }

    return LIS2DH12_STATUS_ERROR;
}

LIS2DH12StatusType LIS2DH12Sensor::enableLowPower() {
    if (!LIS2DH12_Write_LowPower((void*)this, LIS2DH12_LOWPOWER_ENABLE)) {
        return LIS2DH12_STATUS_ERROR;
    }

    
    if (disableHighResolution() == LIS2DH12_STATUS_ERROR) {
        return LIS2DH12_STATUS_ERROR;
    }

    operatingMode_ = LIS2DH12_MODE_LOW_POWER;

    return LIS2DH12_STATUS_OK;
}

LIS2DH12StatusType LIS2DH12Sensor::disableLowPower() {
    if (!LIS2DH12_Write_LowPower((void*)this, LIS2DH12_LOWPOWER_DISABLE)) {
        return LIS2DH12_STATUS_ERROR;
    }

    operatingMode_ = LIS2DH12_MODE_NORMAL;

    return LIS2DH12_STATUS_OK;
}

LIS2DH12StatusType LIS2DH12Sensor::enableHighResolution() {
    if (!LIS2DH12_Write_HighResolution((void*)this, LIS2DH12_HIGH_RESOLUTION_ENABLE)) {
        return LIS2DH12_STATUS_ERROR;
    }

    if (disableLowPower() == LIS2DH12_STATUS_ERROR) {
        return LIS2DH12_STATUS_ERROR;
    }

    operatingMode_ = LIS2DH12_MODE_HIGH_RESOLUTION;

    return LIS2DH12_STATUS_OK;
}

LIS2DH12StatusType LIS2DH12Sensor::disableHighResolution() {
    if (!LIS2DH12_Write_HighResolution((void*)this, LIS2DH12_HIGH_RESOLUTION_DISABLE)) {
        return LIS2DH12_STATUS_ERROR;
    }

    operatingMode_ = LIS2DH12_MODE_NORMAL;

    return LIS2DH12_STATUS_OK;
}

LIS2DH12StatusType LIS2DH12Sensor::setFullScale(LIS2DH12_FS_t fullScale) {
    if (!LIS2DH12_Write_FS((void*)this, fullScale)) {
        return LIS2DH12_STATUS_ERROR;
    }

    return LIS2DH12_STATUS_OK;
}

LIS2DH12StatusType LIS2DH12Sensor::getFullScale(LIS2DH12_FS_t *fullScale) {
    if (!LIS2DH12_Read_FS((void*)this, fullScale)) {
        return LIS2DH12_STATUS_ERROR;
    }

    return LIS2DH12_STATUS_OK;
}

LIS2DH12StatusType LIS2DH12Sensor::getRawAxes(int16_t *axes) {
    if (!LIS2DH12_Read_Axes_Raw((void*)this, axes)) {
        return LIS2DH12_STATUS_ERROR;
    }

    return LIS2DH12_STATUS_OK;
}

LIS2DH12StatusType LIS2DH12Sensor::getAxes(int16_t *axes) {
    int16_t rawAxes[3] = {0};
    if (getRawAxes(rawAxes) == LIS2DH12_STATUS_ERROR) {
        return LIS2DH12_STATUS_ERROR;
    }

    int16_t xRaw = rawAxes[0];
    int16_t yRaw = rawAxes[1];
    int16_t zRaw = rawAxes[2];

    int16_t shiftFactor = 0;
    switch (operatingMode_) {
        case LIS2DH12_MODE_HIGH_RESOLUTION:
            shiftFactor = 4;
            break;
        case LIS2DH12_MODE_LOW_POWER:
            shiftFactor = 8;
            break;
        case LIS2DH12_MODE_NORMAL:
            shiftFactor = 6;
            break;
    }

    xRaw = xRaw >> shiftFactor;
    yRaw = yRaw >> shiftFactor;
    zRaw = zRaw >> shiftFactor;

    int16_t sensitivity = 1;
    LIS2DH12_FS_t fullScale;

    if (getFullScale(&fullScale) == LIS2DH12_STATUS_ERROR) {
        return LIS2DH12_STATUS_ERROR;
    }

    if (fullScale == LIS2DH12_FS_2g) {
        switch (operatingMode_) {
            case LIS2DH12_MODE_HIGH_RESOLUTION:
                sensitivity = 1;
                break;
            case LIS2DH12_MODE_NORMAL:
                sensitivity = 4;
                break;
            case LIS2DH12_MODE_LOW_POWER:
                sensitivity = 16;
                break;
        }
    } else if (fullScale == LIS2DH12_FS_4g) {
        switch (operatingMode_) {
            case LIS2DH12_MODE_HIGH_RESOLUTION:
                sensitivity = 2;
                break;
            case LIS2DH12_MODE_NORMAL:
                sensitivity = 8;
                break;
            case LIS2DH12_MODE_LOW_POWER:
                sensitivity = 32;
                break;
        }
    } else if (fullScale == LIS2DH12_FS_8g) {
        switch (operatingMode_) {
            case LIS2DH12_MODE_HIGH_RESOLUTION:
                sensitivity = 4;
                break;
            case LIS2DH12_MODE_NORMAL:
                sensitivity = 16;
                break;
            case LIS2DH12_MODE_LOW_POWER:
                sensitivity = 64;
                break;
        }
    } else if (fullScale == LIS2DH12_FS_16g) {
        switch (operatingMode_) {
            case LIS2DH12_MODE_HIGH_RESOLUTION:
                sensitivity = 12;
                break;
            case LIS2DH12_MODE_NORMAL:
                sensitivity = 48;
                break;
            case LIS2DH12_MODE_LOW_POWER:
                sensitivity = 192;
                break;
        }
    }

    axes[0] = xRaw * sensitivity;
    axes[1] = yRaw * sensitivity;
    axes[2] = zRaw * sensitivity;

    return LIS2DH12_STATUS_OK;
}

uint8_t LIS2DH12_IO_Write(void *handle, uint8_t address, uint8_t *buffer, uint16_t length) {
    return ((LIS2DH12Sensor*)handle)->write(buffer, address, length);
}

uint8_t LIS2DH12_IO_Read(void *handle, uint8_t address, uint8_t *buffer, uint16_t length) {
    return ((LIS2DH12Sensor*)handle)->read(buffer, address, length);
}
