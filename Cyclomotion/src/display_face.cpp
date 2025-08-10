#include "display_face.h"
#include "config.h"
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 displayFace(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void display_face_setup() {
    displayFace.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR_FACE);
    displayFace.clearDisplay(); displayFace.display();
}

void drawFaceForStatus(Adafruit_SSD1306 &disp, BikeStatus status) {
    disp.clearDisplay();
    switch (status) {
        case TURN_LEFT:  drawFaceHappyLeft(disp);   break;
        case TURN_RIGHT: drawFaceHappyRight(disp);  break;
        case SHAKING:    drawFaceDizzy(disp);       break;
        case STRAIGHT:   drawFaceHappy(disp);       break;
        case STOPPED:    drawFaceNeutral(disp);     break;
    }
}

// Mặt cười (đi thẳng)
void drawFaceHappy(Adafruit_SSD1306 &disp) {
  disp.fillCircle(40, 24, 7, SSD1306_WHITE);
  disp.fillCircle(88, 24, 7, SSD1306_WHITE);
  for (int i = 0; i < 32; i++) {
    int y = 48 + 4 + (int)(4 * sin((float)i / 32 * 3.14159));
    disp.drawPixel(48 + i, y, SSD1306_WHITE);
  }
}

// Mặt cười lệch trái, có mũi tên
void drawFaceHappyLeft(Adafruit_SSD1306 &disp) {
  disp.fillCircle(32, 24, 7, SSD1306_WHITE);
  disp.fillCircle(80, 24, 7, SSD1306_WHITE);
  for (int i = 0; i < 32; i++) {
    int y = 48 + 4 + (int)(4 * sin((float)i / 32 * 3.14159));
    disp.drawPixel(48 + i, y, SSD1306_WHITE);
  }
  drawLeftArrow(disp, 8, 12, 18, 14);
}

// Mặt cười lệch phải, có mũi tên
void drawFaceHappyRight(Adafruit_SSD1306 &disp) {
  disp.fillCircle(48, 24, 7, SSD1306_WHITE);
  disp.fillCircle(96, 24, 7, SSD1306_WHITE);
  for (int i = 0; i < 32; i++) {
    int y = 48 + 4 + (int)(4 * sin((float)i / 32 * 3.14159));
    disp.drawPixel(48 + i, y, SSD1306_WHITE);
  }
  drawRightArrow(disp, 102, 12, 18, 14);
}

// Mặt chán (dừng lại)
void drawFaceNeutral(Adafruit_SSD1306 &disp) {
  disp.fillCircle(40, 24, 5, SSD1306_WHITE);
  disp.fillCircle(88, 24, 5, SSD1306_WHITE);
  disp.drawLine(54, 48, 86, 48, SSD1306_WHITE);
}

// Mặt chóng mặt
void drawFaceDizzy(Adafruit_SSD1306 &disp) {
  int shake = 2 * sin(millis() / 70.0);
  disp.drawLine(36+shake, 18, 44+shake, 30, SSD1306_WHITE);
  disp.drawLine(44+shake, 18, 36+shake, 30, SSD1306_WHITE);
  disp.drawLine(84-shake, 18, 92-shake, 30, SSD1306_WHITE);
  disp.drawLine(92-shake, 18, 84-shake, 30, SSD1306_WHITE);
  int x = 52, y = 52, zigzagLength = 24, amp = 4, step = 4;
  for (int i = 0; i < zigzagLength; i += step) {
    int y1 = y + ((i/step)%2==0?amp:-amp);
    int y2 = y + (((i/step)+1)%2==0?amp:-amp);
    disp.drawLine(x + i, y1, x + i + step, y2, SSD1306_WHITE);
  }
}

// --- Mũi tên ---
void drawLeftArrow(Adafruit_SSD1306 &disp, int x, int y, int w, int h) {
  disp.drawLine(x + w - 2, y + h / 2, x + 2, y + h / 2, SSD1306_WHITE);
  disp.drawLine(x + 2, y + h / 2, x + 8, y + h / 2 - 6, SSD1306_WHITE);
  disp.drawLine(x + 2, y + h / 2, x + 8, y + h / 2 + 6, SSD1306_WHITE);
}

void drawRightArrow(Adafruit_SSD1306 &disp, int x, int y, int w, int h) {
  disp.drawLine(x + 2, y + h / 2, x + w - 2, y + h / 2, SSD1306_WHITE);
  disp.drawLine(x + w - 2, y + h / 2, x + w - 8, y + h / 2 - 6, SSD1306_WHITE);
  disp.drawLine(x + w - 2, y + h / 2, x + w - 8, y + h / 2 + 6, SSD1306_WHITE);
}