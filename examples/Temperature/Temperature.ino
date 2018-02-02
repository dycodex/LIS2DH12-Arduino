#include <Arduino.h>
#include <Wire.h>
#include <LIS2DH12Sensor.h>

LIS2DH12Sensor *accelerometer;

void setup() {
    Serial.begin(9600);
    
    accelerometer = new LIS2DH12Sensor(&Wire);
    if (accelerometer->begin() == LIS2DH12_STATUS_ERROR) {
        Serial.println("Failed initializing accelerometer!");
    }

    if (accelerometer->enableTemperature() == LIS2DH12_STATUS_ERROR) {
        Serial.println("Failed enabling temperature!");
    }
}

void loop() {
    int16_t temp;
    accelerometer->readTemperature(&temp);

    Serial.print("Temperature: ");
    Serial.println(temp);

    delay(1000);
}
