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

int LIS2DH12_Write_LIR_I1(void *handle, LIS2DH12_LatchInterrupt_I1_t latch) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_CTRL_REG5, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_LIR_I1_MASK;
    value |= (uint8_t)latch;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_CTRL_REG5, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_IA_I1(void* handle, LIS2DH12_IA_I1_t IA) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_CTRL_REG3, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_IA_I1_MASK;
    value |= (uint8_t)IA;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_CTRL_REG3, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_INT1_AOI(void* handle, LIS2DH12_INT1_AOI_t AOI) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_INT1_AOI_MASK;
    value |= (uint8_t)AOI;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_INT1_ZHIE(void* handle, LIS2DH12_INT1_ZHIE_t ZHIE) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_INT1_ZHIE_MASK;
    value |= (uint8_t)ZHIE;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_INT1_YHIE(void* handle, LIS2DH12_INT1_YHIE_t YHIE) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_INT1_YHIE_MASK;
    value |= (uint8_t)YHIE;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_INT1_XHIE(void* handle, LIS2DH12_INT1_XHIE_t XHIE) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_INT1_XHIE_MASK;
    value |= (uint8_t)XHIE;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_INT1_6D(void* handle, LIS2DH12_INT1_6D_t sixD) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_INT1_6D_MASK;
    value |= (uint8_t)sixD;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_INT1_THS(void* handle, uint8_t threshold) {
    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_INT1_THS, &threshold, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_INT1_DURATION(void* handle, uint8_t duration) {
    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_INT1_DURATION, &duration, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Read_INT1_SRC(void* handle, uint8_t *source) {
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_INT1_SRC, source, 1)) {
        return 0;
    }

    return 1;
}


int LIS2DH12_Write_INT1_ZLIE(void* handle, LIS2DH12_INT1_ZLIE_t ZLIE) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_INT1_ZLIE_MASK;
    value |= (uint8_t)ZLIE;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_INT1_YLIE(void* handle, LIS2DH12_INT1_YLIE_t YLIE) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_INT1_YLIE_MASK;
    value |= (uint8_t)YLIE;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_INT1_XLIE(void* handle, LIS2DH12_INT1_XLIE_t XLIE) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_INT1_XLIE_MASK;
    value |= (uint8_t)XLIE;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_INT1_CFG, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Read_Who_Am_I(void* handle, uint8_t *ID) {
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_WHO_AM_I, ID, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Write_Temp(void* handle, LIS2DH12_Temp_t temp) {
    uint8_t value;
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_TEMP_CFG_REG, &value, 1)) {
        return 0;
    }

    value &= ~LIS2DH12_TEMP_MASK;
    value |= (uint8_t)temp;

    if (!LIS2DH12_WriteRegister(handle, LIS2DH12_REG_TEMP_CFG_REG, &value, 1)) {
        return 0;
    }

    return 1;
}

int LIS2DH12_Read_Temp(void* handle, int16_t *temperature) {
    uint8_t values[2];
    if (!LIS2DH12_ReadRegister(handle, LIS2DH12_REG_OUT_TEMP_L, values, 2)) {
        return 0;
    }

    *temperature = (int16_t)values[0] | ((int16_t)values[1] << 8);

    return 1;
}
