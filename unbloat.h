#pragma once

#include <Servo.h>
#include <Arduino.h>

extern Servo FrontLeft, FrontRight, BackLeft, BackRight;

// Nuty (tylko używane)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_C6  1047
#define NOTE_D6  1175
#define NOTE_REST 0

const byte PIN_VBAT   = A3;
const byte PIN_STL    = A0;
const byte PIN_STR    = A1;
const byte PIN_SBL    = A2;
const byte PIN_SBR    = 6;
const byte PIN_BUZZER = 8;
const byte PIN_BUTTON = 4;

const byte CENTER_STL = 70;
const byte CENTER_STR = 100;
const byte CENTER_SBL = 70;
const byte CENTER_SBR = 110;

const byte STEP  = 20;
const byte MIN_A = 20;
const byte MAX_A = 160;

const byte DIR_STL = 1, DIR_STR = 1, DIR_SBL = 1, DIR_SBR = 1;

int  clampAngle(int a);
void setAll(byte stl, byte str, byte sbl, byte sbr);
void centerAll();
void sleep();
void walk();
float readBatteryVoltage();