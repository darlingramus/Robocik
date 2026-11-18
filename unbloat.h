#pragma once

#include <Servo.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

extern Servo FrontLeft, FrontRight, BackLeft, BackRight;
extern volatile bool stopFlag;

#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G4  392
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A4  440
#define NOTE_A5  880
#define NOTE_F4  349
#define NOTE_REST 0
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_FS4 370
#define NOTE_GS4 415
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175

// Dzielnik napiecia
const byte PIN_VBAT = A3;

// Piny servo 
const byte PIN_STL = A0;
const byte PIN_STR = A1;
const byte PIN_SBL = A2;
const byte PIN_SBR = 6;

// Centrowanie
const byte CENTER_STL = 70;
const byte CENTER_STR = 100;
const byte CENTER_SBL = 70;
const byte CENTER_SBR = 110;

// Basic UART
const byte rxPin = 2;
const byte txPin = 3;

// "bezpieczne" katy
const byte STEP = 20;
const byte MIN_A = 20;
const byte MAX_A = 160;

// Do tylu
const byte DIR_STL = 1;
const byte DIR_STR = 1;
const byte DIR_SBL = 1;
const byte DIR_SBR = 1;

// Buzzer
const byte PIN_BUZZER = 8;

// TTP223
const byte PIN_BUTTON = 4;

//poruszanie sie
const byte LIFT = 30;         // o ile unosimy nogę (stopnie)
const int  STEP_HOLD  = 500;  // ms trzymania pozycji
const int  STEP_PAUSE = 200;  // ms przerwy w neutralu

int clampAngle(int a);
void setAll(byte stl, byte str, byte sbl, byte sbr);
void centerAll();
void stepForward();
void stepBackward();
void turnLeft();
void turnRight();
void chill();
void sleep();
void dance();
void neutral();
void setLegs(byte fl, byte fr, byte bl, byte br);
void walk();
void happyDance();
float readBatteryVoltage();