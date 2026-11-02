#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h> 
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3D

extern Adafruit_SH1106G display; 

extern float readBatteryVoltage();

void showFace(const char* text, uint8_t sx, uint8_t sy);
void faceHappy();
void faceChill();
void faceSleep();