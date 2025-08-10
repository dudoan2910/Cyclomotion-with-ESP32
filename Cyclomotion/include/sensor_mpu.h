#pragma once
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
void sensor_mpu_setup();
void sensor_mpu_update();
extern Adafruit_MPU6050 mpu;
extern sensors_event_t a, g, temp;
