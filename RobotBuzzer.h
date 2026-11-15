#pragma once

#include "unbloat.h"

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

const int melody[] PROGMEM = {
  NOTE_A4, 500, NOTE_A4, 500, NOTE_A4, 500,
  NOTE_F4, 375, NOTE_C5, 125,
  NOTE_A4, 500, NOTE_F4, 375, NOTE_C5, 125,
  NOTE_A4, 1000,

  NOTE_E5, 500, NOTE_E5, 500, NOTE_E5, 500,
  NOTE_F5, 375, NOTE_C5, 125,
  NOTE_A4, 500, NOTE_F4, 375, NOTE_C5, 125,
  NOTE_A4, 1000,

  NOTE_A5, 500, NOTE_A4, 375, NOTE_A4, 125,
  NOTE_A5, 500, NOTE_GS5, 375, NOTE_G5, 125,
  NOTE_FS5, 125, NOTE_F5, 125, NOTE_FS5, 250,
  NOTE_AS4, 250, NOTE_DS5, 500, NOTE_D5, 375, NOTE_CS5, 125,
  NOTE_C5, 125, NOTE_B4, 125, NOTE_C5, 250,
  NOTE_F4, 250, NOTE_AS4, 500, NOTE_A4, 375, NOTE_G4, 125,
  NOTE_F4, 125, NOTE_E5, 125, NOTE_F4, 250,
  NOTE_AS4, 250, NOTE_CS5, 500, NOTE_C5, 375, NOTE_B4, 125,
  NOTE_C5, 125, NOTE_F4, 125, NOTE_F4, 125, NOTE_F4, 250,
  NOTE_F4, 250, NOTE_F4, 500
};

const int melodyLen = sizeof(melody) / sizeof(melody[0]) / 2;

void ImperialMarch() {
  if (!ensureStanding()) return;
  gaitBegin(+1, +1, true);   // ten sam chod co 'W', tylko w petli i nieblokujacy

  for (int i = 0; i < melodyLen; i++) {
    if (shouldStop()) {
      noTone(PIN_BUZZER);
      gaitStop();
      return;
    }

    int note = pgm_read_word(&melody[i * 2]);
    int dur  = pgm_read_word(&melody[i * 2 + 1]);

    if (note == NOTE_REST) {
      noTone(PIN_BUZZER);
    } else {
      tone(PIN_BUZZER, note, dur);
    }

    unsigned long noteEnd = millis() + (unsigned long)(dur * 1.3);

    while ((long)(millis() - noteEnd) < 0) {
      if (shouldStop()) {
        noTone(PIN_BUZZER);
        gaitStop();
        return;
      }
      gaitUpdate();
    }

    noTone(PIN_BUZZER);
  }

  gaitStop();
}

void WallE_Hello() {
  tone(PIN_BUZZER, 262, 250);
  delay(300);
  tone(PIN_BUZZER, 330, 250);
  delay(300);
  tone(PIN_BUZZER, 392, 250);
  delay(300);
  tone(PIN_BUZZER, 523, 500);
  delay(550);
  noTone(PIN_BUZZER);
}