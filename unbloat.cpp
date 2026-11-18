#include "unbloat.h"

Servo FrontLeft, FrontRight, BackLeft, BackRight;

int clampAngle(int a) {
  if (a < MIN_A) return MIN_A;
  if (a > MAX_A) return MAX_A;
  return a;
}

void setAll(byte stl, byte str, byte sbl, byte sbr) {
  FrontLeft.write (clampAngle(CENTER_STL + DIR_STL * (stl - CENTER_STL)));
  FrontRight.write(clampAngle(CENTER_STR + DIR_STR * (str - CENTER_STR)));
  BackLeft.write (clampAngle(CENTER_SBL + DIR_SBL * (sbl - CENTER_SBL)));
  BackRight.write(clampAngle(CENTER_SBR + DIR_SBR * (sbr - CENTER_SBR)));
}

void centerAll() { 
  setAll(CENTER_STL, CENTER_STR, CENTER_SBL, CENTER_SBR);
  }

void sleep() {
  setAll(20, MAX_A, 160, MIN_A);
  delay(1000);
}

float readBatteryVoltage() {
  return analogRead(PIN_VBAT) * (1.1 / 1023.0) * 7.666;
}

void walk() {
  setAll(CENTER_STL - 30, CENTER_STR, CENTER_SBL, CENTER_SBR - 30);
  delay(500);
  centerAll();
  delay(200);
  setAll(CENTER_STL, CENTER_STR - 30, CENTER_SBL - 30, CENTER_SBR);
  delay(500);
  centerAll();
  delay(200);
}