#include "bike_status.h"
BikeStatus currentStatus = STOPPED;
unsigned long statusHoldUntil = 0;
const unsigned long STATUS_HOLD_TIME = 1000;

void bike_status_update() {
    BikeStatus detectedStatus;
    if (speed * 3.6 < 0.5) {
        detectedStatus = STOPPED;
    } else if (a.acceleration.y > 1.0) {
        detectedStatus = TURN_LEFT;
    } else if (a.acceleration.y < -1.0) {
        detectedStatus = TURN_RIGHT;
    } else if (a.acceleration.z > 2.0) {
        detectedStatus = SHAKING;
    } else {
        detectedStatus = STRAIGHT;
    }
    unsigned long now = millis();
    if (detectedStatus == TURN_LEFT || detectedStatus == TURN_RIGHT || detectedStatus == SHAKING) {
        if (currentStatus != detectedStatus) {
            currentStatus = detectedStatus;
            statusHoldUntil = now + STATUS_HOLD_TIME;
        } else {
            statusHoldUntil = now + STATUS_HOLD_TIME;
        }
    } else if (detectedStatus == STRAIGHT || detectedStatus == STOPPED) {
        if (now > statusHoldUntil) {
            currentStatus = detectedStatus;
        }
    }
}
