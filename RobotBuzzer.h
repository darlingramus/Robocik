#pragma once

#include "unbloat.h"

extern volatile bool stopFlag;

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

const int melodyMegalovania[] PROGMEM = {
  // Główny motyw (D - D - D6 - A - G# - G - F - D - F - G)
  NOTE_D5, 150, NOTE_D5, 150, NOTE_D6, 300, NOTE_A4, 200,
  NOTE_GS5, 150, NOTE_G5, 150, NOTE_F5, 150, NOTE_D5, 150,
  NOTE_F5, 150, NOTE_G5, 150,
  
  // Powtórka z wyższym akcentem
  NOTE_C5, 150, NOTE_C5, 150, NOTE_D6, 300, NOTE_A4, 200,
  NOTE_GS5, 150, NOTE_G5, 150, NOTE_F5, 150, NOTE_D5, 150,
  NOTE_F5, 150, NOTE_G5, 150,

  // Kolejna część (D - D - D6 - A - G# - G - F - D - F - G)
  NOTE_D5, 150, NOTE_D5, 150, NOTE_D6, 300, NOTE_A4, 200,
  NOTE_GS5, 150, NOTE_G5, 150, NOTE_F5, 150, NOTE_D5, 150,
  NOTE_F5, 150, NOTE_G5, 150,

  // Zakończenie (C - C - D6 - A - G# - G - F - D - F - G)
  NOTE_C5, 150, NOTE_C5, 150, NOTE_D6, 300, NOTE_A4, 200,
  NOTE_GS5, 150, NOTE_G5, 150, NOTE_F5, 150, NOTE_D5, 150,
  NOTE_F5, 150, NOTE_G5, 150
};
const int megalovaniaLen = sizeof(melodyMegalovania) / sizeof(melodyMegalovania[0]) / 2;

const int melodyLen = sizeof(melody) / sizeof(melody[0]) / 2;

// Czas jednej fazy kroku (ms) - tyle samo co delay() w stepForward()
const unsigned long GAIT_PHASE_MS = 150;

// Stan chodu - nieblokujący, sterowany przez millis()
static unsigned long gaitLast = 0;
static bool gaitStepOut = false;

static void gaitStart() {
  gaitStepOut = true;
  gaitLast = millis();
  // pierwsza faza kroku do przodu (jak w stepForward)
  setAll(CENTER_STL + STEP, CENTER_STR + STEP,
         CENTER_SBL - STEP, CENTER_SBR - STEP);
}

static void gaitUpdate() {
  if (millis() - gaitLast >= GAIT_PHASE_MS) {
    gaitLast += GAIT_PHASE_MS;
    gaitStepOut = !gaitStepOut;
    if (gaitStepOut) {
      setAll(CENTER_STL + STEP, CENTER_STR + STEP,
             CENTER_SBL - STEP, CENTER_SBR - STEP);
    } else {
      centerAll();
    }
  }
}

void ImperialMarch() {
  gaitStart();

  for (int i = 0; i < melodyLen; i++) {

    int note = pgm_read_word(&melody[i * 2]);
    int dur  = pgm_read_word(&melody[i * 2 + 1]);

    if (note == NOTE_REST) {
      noTone(PIN_BUZZER);
    } else {
      tone(PIN_BUZZER, note, dur);
    }

    unsigned long noteEnd = millis() + (unsigned long)(dur * 1.3);
    
    while ((long)(millis() - noteEnd) < 0) {
      gaitUpdate();
    }

    noTone(PIN_BUZZER);
  }

  centerAll();
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

void lullabyStar() {
  tone(PIN_BUZZER, NOTE_C5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_C5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_G5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_G5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_A5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_A5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_G5, 800); delay(900);
  
  tone(PIN_BUZZER, NOTE_F5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_F5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_E5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_E5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_D5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_D5, 400); delay(500);
  tone(PIN_BUZZER, NOTE_C5, 800); delay(900);
  
  noTone(PIN_BUZZER);
}

void MegalovaniaDance() {
  // Ustawiamy nogi w pozycji wyjściowej
  centerAll();
  
  for (int i = 0; i < megalovaniaLen; i++) {
    int note = pgm_read_word(&melodyMegalovania[i * 2]);
    int dur  = pgm_read_word(&melodyMegalovania[i * 2 + 1]);

    if (note == NOTE_REST) {
      noTone(PIN_BUZZER);
    } else {
      tone(PIN_BUZZER, note, dur);
    }

    // Taniec w rytm muzyki (co drugi dźwięk podnosimy inną parę nóg)
    if (i % 2 == 0) {
      setLegs(CENTER_STL - 30, CENTER_STR - 30, CENTER_SBL, CENTER_SBR); // Przód w górę
    } else {
      setLegs(CENTER_STL, CENTER_STR, CENTER_SBL - 30, CENTER_SBR - 30); // Tył w górę
    }

    // --- ZMIANA: Czekamy przez czas trwania nuty ---
    // Mnożymy przez 1.3, tak jak w ImperialMarch, żeby zachować rytm
    delay((int)(dur * 1.3)); 

    noTone(PIN_BUZZER);
  }

  centerAll();
}
