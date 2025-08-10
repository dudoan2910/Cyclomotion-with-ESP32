#include "sensor_mpu.h"
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

void sensor_mpu_setup() {
    if (!mpu.begin()) {
        Serial.println("Không tìm thấy MPU6050");
        while (1);
    }
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void sensor_mpu_update() {
    mpu.getEvent(&a, &g, &temp);
}
