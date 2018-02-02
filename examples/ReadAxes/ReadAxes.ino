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
}

void loop() {
    int16_t axes[3];
    accelerometer->getAxes(axes);

    Serial.print("X = ");
    Serial.println(axes[0]);
    Serial.print("Y = ");
    Serial.println(axes[1]);
    Serial.print("Z = ");
    Serial.println(axes[2]);

    delay(1000);
}
