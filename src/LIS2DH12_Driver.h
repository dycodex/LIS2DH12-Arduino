#ifndef __LIS2DH12_DRIVER_H__
#define __LIS2DH12_DRIVER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// I2C Address
#define LIS2DH12_I2C_ADDRESS 0x18

// Register Addresses
#define LIS2DH12_REG_OUT_TEMP_L 0x0C
#define LIS2DH12_REG_WHO_AM_I 0x0F
#define LIS2DH12_REG_TEMP_CFG_REG 0x1F
#define LIS2DH12_REG_CTRL_REG1 0x20
#define LIS2DH12_REG_CTRL_REG2 0x21
#define LIS2DH12_REG_CTRL_REG3 0x22
#define LIS2DH12_REG_CTRL_REG4 0x23
#define LIS2DH12_REG_CTRL_REG5 0x24
#define LIS2DH12_REG_CTRL_REG6 0x25
#define LIS2DH12_REG_STATUS_REG 0x27
#define LIS2DH12_REG_OUT_X_L 0x29
#define LIS2DH12_REG_OUT_Y_L 0x2B
#define LIS2DH12_REG_OUT_Z_L 0x2D
#define LIS2DH12_REG_INT1_CFG 0x30
#define LIS2DH12_REG_INT1_SRC 0x31
#define LIS2DH12_REG_INT1_THS 0x32
#define LIS2DH12_REG_INT1_DURATION 0x33

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

typedef enum {
    LIS2DH12_LIR_I1_ENABLE = 0x08,
    LIS2DH12_LIR_I1_DISABLE = 0x0,
} LIS2DH12_LatchInterrupt_I1_t;

#define LIS2DH12_LIR_I1_MASK 0x08

int LIS2DH12_Write_LIR_I1(void *handle, LIS2DH12_LatchInterrupt_I1_t latch);

typedef enum {
    LIS2DH12_IA1_I1_ENABLE = 0x40,
    LIS2DH12_IA1_I1_DISABLE = 0x00,
} LIS2DH12_IA_I1_t;

#define LIS2DH12_IA_I1_MASK 0x40

int LIS2DH12_Write_IA_I1(void *handle, LIS2DH12_IA_I1_t IA);

typedef enum {
    LIS2DH12_INT1_AOI_AND = 0x80,
    LIS2DH12_INT1_AOI_OR = 0x00,
} LIS2DH12_INT1_AOI_t;

#define LIS2DH12_INT1_AOI_MASK 0x80

int LIS2DH12_Write_INT1_AOI(void* handle, LIS2DH12_INT1_AOI_t AOI);

typedef enum {
    LIS2DH12_INT1_6D_ENABLE = 0x40,
    LIS2DH12_INT1_6D_DISABLE = 0x00,
} LIS2DH12_INT1_6D_t;

#define LIS2DH12_INT1_6D_MASK 0x40

int LIS2DH12_Write_INT1_6D(void* handle, LIS2DH12_INT1_6D_t sixD);

typedef enum {
    LIS2DH12_INT1_ZHIE_ENABLE = 0x20,
    LIS2DH12_INT1_ZHIE_DISABLE = 0x00,
} LIS2DH12_INT1_ZHIE_t;

#define LIS2DH12_INT1_ZHIE_MASK 0x20

int LIS2DH12_Write_INT1_ZHIE(void* handle, LIS2DH12_INT1_ZHIE_t ZHIE);

typedef enum {
    LIS2DH12_INT1_YHIE_ENABLE = 0x08,
    LIS2DH12_INT1_YHIE_DISABLE = 0x00,
} LIS2DH12_INT1_YHIE_t;

#define LIS2DH12_INT1_YHIE_MASK 0x08

int LIS2DH12_Write_INT1_YHIE(void* handle, LIS2DH12_INT1_YHIE_t YHIE);

typedef enum {
    LIS2DH12_INT1_XHIE_ENABLE = 0x02,
    LIS2DH12_INT1_XHIE_DISABLE = 0x00,
} LIS2DH12_INT1_XHIE_t;

#define LIS2DH12_INT1_XHIE_MASK 0x02

int LIS2DH12_Write_INT1_XHIE(void* handle, LIS2DH12_INT1_XHIE_t XHIE);

int LIS2DH12_Write_INT1_THS(void* handle, uint8_t threshold);

int LIS2DH12_Write_INT1_DURATION(void* handle, uint8_t duration);

int LIS2DH12_Read_INT1_SRC(void* handle, uint8_t *source);

typedef enum {
    LIS2DH12_INT1_ZLIE_ENABLE = 0x10,
    LIS2DH12_INT1_ZLIE_DISABLE = 0x00,
} LIS2DH12_INT1_ZLIE_t;

#define LIS2DH12_INT1_ZLIE_MASK 0x10

int LIS2DH12_Write_INT1_ZLIE(void* handle, LIS2DH12_INT1_ZLIE_t ZLIE);

typedef enum {
    LIS2DH12_INT1_YLIE_ENABLE = 0x04,
    LIS2DH12_INT1_YLIE_DISABLE = 0x00,
} LIS2DH12_INT1_YLIE_t;

#define LIS2DH12_INT1_YLIE_MASK 0x04

int LIS2DH12_Write_INT1_YLIE(void* handle, LIS2DH12_INT1_YLIE_t YLIE);

typedef enum {
    LIS2DH12_INT1_XLIE_ENABLE = 0x01,
    LIS2DH12_INT1_XLIE_DISABLE = 0x00,
} LIS2DH12_INT1_XLIE_t;

#define LIS2DH12_INT1_XLIE_MASK 0x01

int LIS2DH12_Write_INT1_XLIE(void* handle, LIS2DH12_INT1_XLIE_t XLIE);

int LIS2DH12_Read_Who_Am_I(void* handle, uint8_t *ID);

typedef enum {
    LIS2DH12_TEMP_ENABLE = 0xC0,
    LIS2DH12_TEMP_DISABLE = 0x00,
} LIS2DH12_Temp_t;

#define LIS2DH12_TEMP_MASK 0xC0

int LIS2DH12_Write_Temp(void* handle, LIS2DH12_Temp_t temp);

int LIS2DH12_Read_Temp(void* handle, int16_t *temperature);

#ifdef __cplusplus
}
#endif

#endif
