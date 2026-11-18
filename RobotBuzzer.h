#pragma once
#include "unbloat.h"

const int melody[] PROGMEM = {
  NOTE_A4,500, NOTE_A4,500, NOTE_A4,500,
  NOTE_F4,375, NOTE_C5,125,
  NOTE_A4,500, NOTE_F4,375, NOTE_C5,125,
  NOTE_A4,1000,
  NOTE_E5,500, NOTE_E5,500, NOTE_E5,500,
  NOTE_F5,375, NOTE_C5,125,
  NOTE_A4,500, NOTE_F4,375, NOTE_C5,125,
  NOTE_A4,1000,
  NOTE_A5,500, NOTE_A4,375, NOTE_A4,125,
  NOTE_A5,500, NOTE_GS5,375, NOTE_G5,125,
  NOTE_FS5,125, NOTE_F5,125, NOTE_FS5,250,
  NOTE_AS4,250, NOTE_DS5,500, NOTE_D5,375, NOTE_CS5,125,
  NOTE_C5,125, NOTE_B4,125, NOTE_C5,250,
  NOTE_F4,250, NOTE_AS4,500, NOTE_A4,375, NOTE_G4,125,
  NOTE_F4,125, NOTE_E5,125, NOTE_F4,250,
  NOTE_AS4,250, NOTE_CS5,500, NOTE_C5,375, NOTE_B4,125,
  NOTE_C5,125, NOTE_F4,125, NOTE_F4,125, NOTE_F4,250,
  NOTE_F4,250, NOTE_F4,500
};
const int melodyLen = sizeof(melody) / sizeof(melody[0]) / 2;

const int melodyMegalovania[] PROGMEM = {
  NOTE_D5,150, NOTE_D5,150, NOTE_D6,300, NOTE_A4,200,
  NOTE_GS5,150, NOTE_G5,150, NOTE_F5,150, NOTE_D5,150,
  NOTE_F5,150, NOTE_G5,150,
  NOTE_C5,150, NOTE_C5,150, NOTE_D6,300, NOTE_A4,200,
  NOTE_GS5,150, NOTE_G5,150, NOTE_F5,150, NOTE_D5,150,
  NOTE_F5,150, NOTE_G5,150,
  NOTE_D5,150, NOTE_D5,150, NOTE_D6,300, NOTE_A4,200,
  NOTE_GS5,150, NOTE_G5,150, NOTE_F5,150, NOTE_D5,150,
  NOTE_F5,150, NOTE_G5,150,
  NOTE_C5,150, NOTE_C5,150, NOTE_D6,300, NOTE_A4,200,
  NOTE_GS5,150, NOTE_G5,150, NOTE_F5,150, NOTE_D5,150,
  NOTE_F5,150, NOTE_G5,150
};
const int megalovaniaLen = sizeof(melodyMegalovania) / sizeof(melodyMegalovania[0]) / 2;

static unsigned long gaitLast = 0;
static bool gaitStepOut = false;

static void gaitUpdate() {
  if (millis() - gaitLast < 150) return;
  gaitLast += 150;
  gaitStepOut = !gaitStepOut;
  if (gaitStepOut)
    setAll(CENTER_STL + STEP, CENTER_STR + STEP,
           CENTER_SBL - STEP, CENTER_SBR - STEP);
  else
    centerAll();
}

void ImperialMarch() {
  gaitStepOut = true; gaitLast = millis();
  setAll(CENTER_STL + STEP, CENTER_STR + STEP,
         CENTER_SBL - STEP, CENTER_SBR - STEP);

  for (int i = 0; i < melodyLen; i++) {
    int note = pgm_read_word(&melody[i*2]);
    int dur  = pgm_read_word(&melody[i*2+1]);
    if (note == NOTE_REST) noTone(PIN_BUZZER);
    else tone(PIN_BUZZER, note, dur);
    unsigned long end = millis() + (unsigned long)(dur * 1.3);
    while ((long)(millis() - end) < 0) gaitUpdate();
    noTone(PIN_BUZZER);
  }
  centerAll();
}

void WallE_Hello() {
  const int n[] = {262, 330, 392, 523};
  for (int i = 0; i < 4; i++) { tone(PIN_BUZZER, n[i], 250); delay(300); }
  noTone(PIN_BUZZER);
}

void lullabyStar() {
  const int n[] = {NOTE_C5,NOTE_C5,NOTE_G5,NOTE_G5,NOTE_A5,NOTE_A5,NOTE_G5,
                   NOTE_F5,NOTE_F5,NOTE_E5,NOTE_E5,NOTE_D5,NOTE_D5,NOTE_C5};
  for (int i = 0; i < 14; i++) {
    tone(PIN_BUZZER, n[i], (i==6||i==13)?800:400);
    delay((i==6||i==13)?900:500);
  }
  noTone(PIN_BUZZER);
}

void MegalovaniaDance() {
  centerAll();
  for (int i = 0; i < megalovaniaLen; i++) {
    int note = pgm_read_word(&melodyMegalovania[i*2]);
    int dur  = pgm_read_word(&melodyMegalovania[i*2+1]);
    if (note == NOTE_REST) noTone(PIN_BUZZER);
    else tone(PIN_BUZZER, note, dur);

    if (i % 2 == 0)
      setAll(CENTER_STL-30, CENTER_STR-30, CENTER_SBL, CENTER_SBR);
    else
      setAll(CENTER_STL, CENTER_STR, CENTER_SBL-30, CENTER_SBR-30);

    delay((int)(dur * 1.3));
    noTone(PIN_BUZZER);
  }
  centerAll();
}