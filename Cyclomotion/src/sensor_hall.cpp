#include "sensor_hall.h"
#include "config.h"
#include <Arduino.h>

volatile unsigned long wheel_count = 0;
volatile unsigned long last_pulse_time = 0;
volatile unsigned long pulse_interval = 0;
float wheel_circumference = 2.1; // (m)
float total_distance = 0.0;
float speed = 0.0;

void IRAM_ATTR onHallSensor() {
    unsigned long now = millis();
    if (last_pulse_time > 0) {
        pulse_interval = now - last_pulse_time;
    }
    last_pulse_time = now;
    wheel_count++;
}

void sensor_hall_setup() {
    pinMode(HALL_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(HALL_PIN), onHallSensor, FALLING);
}

void sensor_hall_update() {
    static unsigned long last_checked_pulse = 0;
    static unsigned long last_wheel_count = 0;

    noInterrupts();
    unsigned long local_count = wheel_count;
    unsigned long interval = pulse_interval;
    unsigned long pulse_time = last_pulse_time;
    interrupts();

    if (local_count > last_wheel_count) {
        total_distance += (local_count - last_wheel_count) * wheel_circumference;
        last_wheel_count = local_count;
    }

    if (interval > 0 && (pulse_time != last_checked_pulse)) {
        speed = wheel_circumference / (interval / 1000.0); // m/s
        last_checked_pulse = pulse_time;
    }

    if (millis() - pulse_time > 2000) {
        speed = 0;
    }
}
