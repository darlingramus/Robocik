#pragma once

#include <Servo.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

extern Servo STL, STR, SBL, SBR;

// Dzielnik napiecia
const byte PIN_VBAT = A3;

// Piny servo 
const byte PIN_STL = A0;
const byte PIN_STR = A1;
const byte PIN_SBL = A2;
const byte PIN_SBR = 6;

// Centrowanie
const byte CENTER_STL = 90;
const byte CENTER_STR = 90;
const byte CENTER_SBL = 90;
const byte CENTER_SBR = 90;

// Basic UART
const byte rxPin = 2;
const byte txPin = 3;

// "bezpieczne" katy
const byte STEP = 20;
const byte MIN_A = 20;
const byte MAX_A = 160;

// Do tylu
const byte DIR_STL = +1;
const byte DIR_STR = -1;
const byte DIR_SBL = +1;
const byte DIR_SBR = -1;

// Buzzer
const byte PIN_BUZZER = 8;

// TTP223
const byte PIN_BUTTON = 4;

int clampAngle(int a);
void setAll(byte stl, byte str, byte sbl, byte sbr);
void centerAll();
void stepForward();
void stepBackward();
void turnLeft();
void turnRight();
void chill();
void sleep();
float readBatteryVoltage();