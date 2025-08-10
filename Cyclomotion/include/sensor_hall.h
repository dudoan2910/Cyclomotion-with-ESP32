#pragma once
#include <Arduino.h>  

void sensor_hall_setup();
void sensor_hall_update();

extern volatile unsigned long wheel_count, last_pulse_time, pulse_interval;
extern float wheel_circumference, total_distance, speed;

void IRAM_ATTR onHallSensor();
