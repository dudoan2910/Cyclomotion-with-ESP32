#pragma once
#include "sensor_mpu.h"
#include "sensor_hall.h"
enum BikeStatus {
    STRAIGHT,
    TURN_LEFT,
    TURN_RIGHT,
    SHAKING,
    STOPPED
};
extern BikeStatus currentStatus;
extern unsigned long statusHoldUntil;
extern const unsigned long STATUS_HOLD_TIME;
void bike_status_update();
