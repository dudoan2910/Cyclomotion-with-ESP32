#include "display_main.h"
#include "config.h"
#include "sensor_mpu.h"
#include "sensor_hall.h"
#include "sensor_vl53l0x.h"
#include "bike_status.h"
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 displayMain(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void display_main_setup() {
    displayMain.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR_MAIN);
    displayMain.clearDisplay(); displayMain.display();
}

void displayBikeInfo() {
    displayMain.clearDisplay();
    displayMain.setTextColor(SSD1306_WHITE);
    displayMain.setTextSize(1);
    displayMain.setCursor(0, 0);

    displayMain.print("SPD: ");
    displayMain.print(speed * 3.6, 1); displayMain.println(" km/h");

    displayMain.print("DIST: ");
    displayMain.print(total_distance, 1); displayMain.println(" m");

    displayMain.print("FRONT: ");
    if (distanceFront > 0) {
        displayMain.print(distanceFront);
        displayMain.println(" mm");
    } else {
        displayMain.println("----");
    }

    displayMain.print("AccX: "); displayMain.println(a.acceleration.x, 2);
    displayMain.print("AccY: "); displayMain.println(a.acceleration.y, 2);
    displayMain.print("AccZ: "); displayMain.println(a.acceleration.z, 2);

    displayMain.print("STATE: ");
    switch (currentStatus) {
        case TURN_LEFT:  displayMain.println("Left"); break;
        case TURN_RIGHT: displayMain.println("Right"); break;
        case SHAKING:    displayMain.println("Shaking"); break;
        case STRAIGHT:   displayMain.println("Straight"); break;
        case STOPPED:    displayMain.println("Stopped"); break;
    }
    displayMain.print("TEMP: ");
    displayMain.print(temp.temperature, 1);
    displayMain.println(" C");
}
