#include <Arduino.h>
#include <Wire.h>
#include <LIS2DH12Sensor.h>
#include <LIS2DH12_Driver.h>

LIS2DH12Sensor *accelerometer;

#define INT1_PIN 2
static volatile bool isInterrupted = false;
void interrupted() {
    isInterrupted = true;
}

void setup() {
    Serial.begin(9600);
    
    accelerometer = new LIS2DH12Sensor(&Wire);
    if (accelerometer->begin() == LIS2DH12_STATUS_ERROR) {
        Serial.println("Failed initializing accelerometer!");
    }

    uint8_t disableHighPassFilter = 0x00;
    LIS2DH12_Write_IA_I1(accelerometer, LIS2DH12_IA1_I1_ENABLE);
    LIS2DH12_WriteRegister(accelerometer, LIS2DH12_REG_CTRL_REG2, &disableHighPassFilter, 1);
    LIS2DH12_Write_LIR_I1(accelerometer, LIS2DH12_LIR_I1_ENABLE);
    LIS2DH12_Write_INT1_THS(accelerometer, 0x16);
    LIS2DH12_Write_INT1_DURATION(accelerometer, 0x03);
    LIS2DH12_Write_INT1_AOI(accelerometer, LIS2DH12_INT1_AOI_AND);
    LIS2DH12_Write_INT1_ZHIE(accelerometer, LIS2DH12_INT1_ZHIE_DISABLE);
    LIS2DH12_Write_INT1_XHIE(accelerometer, LIS2DH12_INT1_XHIE_DISABLE);
    LIS2DH12_Write_INT1_YHIE(accelerometer, LIS2DH12_INT1_YHIE_DISABLE);
    LIS2DH12_Write_INT1_ZLIE(accelerometer, LIS2DH12_INT1_ZLIE_ENABLE);
    LIS2DH12_Write_INT1_XLIE(accelerometer, LIS2DH12_INT1_XLIE_ENABLE);
    LIS2DH12_Write_INT1_YLIE(accelerometer, LIS2DH12_INT1_YLIE_ENABLE);

    pinMode(INT1_PIN, INPUT_PULLDOWN);
    attachInterrupt(INT1_PIN, interrupted, RISING);
}

void loop() {
    if (isInterrupted) {
        isInterrupted = false;
        uint8_t intSource;
        if (!LIS2DH12_Read_INT1_SRC(accelerometer, &intSource)) {
            Serial.println("Failed to read interrupt source!");
        } else {
            Serial.print("Interrupt source:");
            Serial.println(intSource, BIN);
        }
    }
}
