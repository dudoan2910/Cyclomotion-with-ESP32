#pragma once
#include <Adafruit_VL53L0X.h>
void sensor_vl53l0x_setup();
void sensor_vl53l0x_update();
extern Adafruit_VL53L0X lox;
extern uint16_t distanceFront;
