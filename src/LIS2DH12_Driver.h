#ifndef __LIS2DH12_DRIVER_H__
#define __LIS2DH12_DRIVER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// I2C Address
#define LIS2DH12_I2C_ADDRESS 0x18

// Register Addresses
#define LIS2DH12_REG_CTRL_REG1 0x20
#define LIS2DH12_REG_CTRL_REG4 0x23
#define LIS2DH12_REG_STATUS_REG 0x27
#define LIS2DH12_REG_OUT_X_L 0x29
#define LIS2DH12_REG_OUT_Y_L 0x2B
#define LIS2DH12_REG_OUT_Z_L 0x2D

int LIS2DH12_WriteRegister(void* handle, uint8_t registerAddress, uint8_t *buffer, uint16_t length);
int LIS2DH12_ReadRegister(void* handle, uint8_t registerAddress, uint8_t *buffer, uint16_t length);

typedef enum {
    LIS2DH12_ODR_1Hz = 0x10,
    LIS2DH12_ODR_10Hz = 0x20,
    LIS2DH12_ODR_25Hz = 0x30,
    LIS2DH12_ODR_50Hz = 0x40,
    LIS2DH12_ODR_100Hz = 0x50,
    LIS2DH12_ODR_200Hz = 0x60,
    LIS2DH12_ODR_400Hz = 0x70,
    LIS2DH12_ODR_1620Hz = 0x80,
    LIS2DH12_ODR_5376Hz = 0x90
} LIS2DH12_ODR_t;

#define LIS2DH12_ODR_MASK 0xF0

int LIS2DH12_Write_ODR(void *handle, LIS2DH12_ODR_t odr);
int LIS2DH12_Read_ODR(void *handle, LIS2DH12_ODR_t *odr);

typedef enum {
    LIS2DH12_ENABLE_X = 0x01,
    LIS2DH12_ENABLE_Y = 0x02,
    LIS2DH12_ENABLE_Z = 0x03
} LIS2DH12_AxesEnable_t;

#define LIS2DH12_AXES_ENABLE_MASK 0x07

int LIS2DH12_Enable_Axes(void *handle, LIS2DH12_AxesEnable_t axes);
int LIS2DH12_Disable_Axes(void *handle);

typedef enum {
    LIS2DH12_LOWPOWER_ENABLE = 0x08,
    LIS2DH12_LOWPOWER_DISABLE = 0x00,
} LIS2DH12_LowPower_t;

#define LIS2DH12_LOWPOWER_MASK 0x08

int LIS2DH12_Write_LowPower(void *handle, LIS2DH12_LowPower_t lowPowerState);

typedef enum {
    LIS2DH12_HIGH_RESOLUTION_ENABLE = 0x08,
    LIS2DH12_HIGH_RESOLUTION_DISABLE = 0x00,
} LIS2DH12_HighResolution_t;

#define LIS2DH12_HIGH_RESOLUTION_MASK 0x08

int LIS2DH12_Write_HighResolution(void *handle, LIS2DH12_HighResolution_t highRes);

typedef enum {
    LIS2DH12_FS_2g = 0x00,
    LIS2DH12_FS_4g = 0x10,
    LIS2DH12_FS_8g = 0x20,
    LIS2DH12_FS_16g = 0x30,
} LIS2DH12_FS_t;

#define LIS2DH12_FS_MASK 0x30

int LIS2DH12_Write_FS(void *handle, LIS2DH12_FS_t fullScale);
int LIS2DH12_Read_FS(void* handle, LIS2DH12_FS_t *fullScale);

int LIS2DH12_Read_Axes_Raw(void* handle, int16_t *axes);

#ifdef __cplusplus
}
#endif

#endif
