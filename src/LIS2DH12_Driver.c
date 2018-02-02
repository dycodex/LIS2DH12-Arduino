#include "LIS2DH12_Driver.h"

extern uint8_t LIS2DH12_IO_Write(void *handle, uint8_t address, uint8_t *buffer, uint16_t length);
extern uint8_t LIS2DH12_IO_Read(void *handle, uint8_t address, uint8_t *buffer, uint16_t length);

int LIS2DH12_WriteRegister(void *handle, uint8_t registerAddress, uint8_t *buffer, uint16_t length) {
    if (LIS2DH12_IO_Write(handle, registerAddress, buffer, length)) {
        return 0;
    } else {
        return 1;
    }
}

int LIS2DH12_ReadRegister(void *handle, uint8_t registerAddress, uint8_t *buffer, uint16_t length) {
    if (LIS2DH12_IO_Read(handle, registerAddress, buffer, length)) {
        return 0;
    } else { 
        return 1;
    }
}

int LIS2DH12_Write_ODR(void *handle, LIS2DH12_ODR_t odr) {
    uint8_t regValue;

    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_CTRL_REG1, &regValue, 1)) {
        return 0;
    }

    regValue &= ~LIS2DH12_ODR_MASK;
    regValue |= odr;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_CTRL_REG1, &regValue, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Read_ODR(void *handle, LIS2DH12_ODR_t *odr) {
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_CTRL_REG1, (uint8_t*)odr, 1)) {
        return 0;
    }

    *odr &= LIS2DH12_ODR_MASK;

    return 1;
}

int LIS2DH12_Enable_Axes(void *handle, LIS2DH12_AxesEnable_t axes) {
    uint8_t value;

    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_CTRL_REG1, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_AXES_ENABLE_MASK;
    value |= axes;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_CTRL_REG1, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Disable_Axes(void *handle) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_CTRL_REG1, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_AXES_ENABLE_MASK;
}

int LIS2DH12_Write_LowPower(void *handle, LIS2DH12_LowPower_t lowPowerState) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_CTRL_REG1, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_LOWPOWER_MASK;
    value |= (uint8_t)lowPowerState;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_CTRL_REG1, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_HighResolution(void *handle, LIS2DH12_HighResolution_t highRes) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_CTRL_REG4, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_HIGH_RESOLUTION_MASK;
    value |= (uint8_t)highRes;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_CTRL_REG4, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_FS(void *handle, LIS2DH12_FS_t fullScale) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_CTRL_REG4, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_FS_MASK;
    value |= (uint8_t)fullScale;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_CTRL_REG4, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Read_FS(void *handle, LIS2DH12_FS_t *fullScale) {
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_CTRL_REG4, (uint8_t*)fullScale, 1)) {
        return 0;
    }

    *fullScale &= LIS2DH12_FS_MASK;

    return 1;
}

int LIS2DH12_Read_Axes_Raw(void *handle, int16_t *axes) {
    uint8_t x[2] = {0};
    uint8_t y[2] = {0};
    uint8_t z[2] = {0};

    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_OUT_X_L, x, 2)) {
        return 0;
    }

    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_OUT_Y_L, y, 2)) {
        return 0;
    }

    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_OUT_Z_L, y, 2)) {
        return 0;
    }

    axes[0] = (int16_t)(x[0]) | (int16_t)(x[1] << 8);
    axes[1] = (int16_t)(y[0]) | (int16_t)(y[1] << 8);
    axes[2] = (int16_t)(z[0]) | (int16_t)(z[1] << 8);

    return 1;
}
