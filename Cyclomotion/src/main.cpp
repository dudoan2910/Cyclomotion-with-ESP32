#include "config.h"
#include "sensor_mpu.h"
#include "sensor_vl53l0x.h"
#include "sensor_hall.h"
#include "bike_status.h"
#include "display_main.h"
#include "display_face.h"
#include <Adafruit_SSD1306.h>

void setup() {
    Serial.begin(115200);
    Wire.begin(OLED_SDA, OLED_SCL);
    Wire.setClock(100000);

    display_main_setup();
    display_face_setup();
    sensor_mpu_setup();
    sensor_vl53l0x_setup();
    sensor_hall_setup();

    delay(1000);
    drawFaceForStatus(displayFace, STOPPED);
    displayFace.display();
}

void loop() {
    static BikeStatus lastFaceStatus = STOPPED;
    static unsigned long last_main_update = 0;
    static unsigned long last_face_update = 0;
    const unsigned long main_interval = 200; // ms
    const unsigned long face_interval = 320;

    sensor_hall_update();
    sensor_mpu_update();
    sensor_vl53l0x_update();
    bike_status_update();

    unsigned long now = millis();

    // Update màn hình chính mỗi 200ms
    if (now - last_main_update > main_interval) {
        displayBikeInfo();
        displayMain.display();
        last_main_update = now;
    }

    // Update mặt biểu cảm mỗi 320ms hoặc khi trạng thái đổi
    if ((now - last_face_update > face_interval) || (currentStatus != lastFaceStatus)) {
        drawFaceForStatus(displayFace, currentStatus);
        displayFace.display();
        last_face_update = now;
        lastFaceStatus = currentStatus;
    }
}
