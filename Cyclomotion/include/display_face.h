#pragma once
#include "bike_status.h"
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 displayFace;

void display_face_setup();
void drawFaceForStatus(Adafruit_SSD1306 &disp, BikeStatus status);
void drawFaceHappy(Adafruit_SSD1306 &disp);
void drawFaceHappyLeft(Adafruit_SSD1306 &disp);
void drawFaceHappyRight(Adafruit_SSD1306 &disp);
void drawFaceNeutral(Adafruit_SSD1306 &disp);
void drawFaceDizzy(Adafruit_SSD1306 &disp);
void drawLeftArrow(Adafruit_SSD1306 &disp, int x, int y, int w, int h);
void drawRightArrow(Adafruit_SSD1306 &disp, int x, int y, int w, int h);
