#include "sensor_vl53l0x.h"
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
uint16_t distanceFront = 0;

void sensor_vl53l0x_setup() {
    lox.begin();
}
void sensor_vl53l0x_update() {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);
    if (measure.RangeStatus != 4 && measure.RangeStatus != 255) {
        distanceFront = measure.RangeMilliMeter;
    } else {
        distanceFront = 0;
    }
}
