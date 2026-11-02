#include "unbloat.h"


Servo STL, STR, SBL, SBR;

int clampAngle(int a) {
  if (a < MIN_A) return MIN_A;
  if (a > MAX_A) return MAX_A;
  return (int)a;
}

// Ustawia pozycje z uwzględnieniem kierunku montażu
void setAll(byte stl, byte str, byte sbl, byte sbr) {
  STL.write(clampAngle(CENTER_STL + DIR_STL * (stl - CENTER_STL)));
  STR.write(clampAngle(CENTER_STR + DIR_STR * (str - CENTER_STR)));
  SBL.write(clampAngle(CENTER_SBL + DIR_SBL * (sbl - CENTER_SBL)));
  SBR.write(clampAngle(CENTER_SBR + DIR_SBR * (sbr - CENTER_SBR)));
}

void centerAll(){
  STL.write(CENTER_STL);
  STR.write(CENTER_STR);
  SBL.write(CENTER_SBL);
  SBR.write(CENTER_SBR);
}

// ---------------------------------------------------------------------------
// CZOŁGANIE (chód po przekątnych, "stick-slip")
//
// Dlaczego stary stepForward stał w miejscu: przód szedł w jedną stronę,
// tył w drugą, a potem wszystko wracało na środek - ruch był symetryczny,
// więc zysk = 0.
//
// Teraz: nogi dzielą się na dwie pary po przekątnej
//   para A = STL + SBR,   para B = STR + SBL
// Każda para po kolei robi:
//   1. SZYBKI wyrzut stopy do przodu   (para odciążona, ślizga się)
//   2. WOLNE przeciągnięcie do tyłu    (para dociśnięta, chwyta - pcha korpus)
//   3. SZYBKI powrót na środek
// Wolny ruch "łapie" podłoże, szybkie ruchy się ślizgają - stąd przesuw.
// ---------------------------------------------------------------------------

// Parametry do dostrojenia
static const int FWD        = +1;  // jeśli robot jedzie do tyłu zamiast do przodu -> zmień na -1
static const int REACH      = STEP; // wychył nogi od środka (stopnie)
static const int FAST_MS    = 70;  // czas szybkich ruchów (wyrzut / powrót)
static const int SLOW_STEPS = 8;   // na ile kroków dzielimy wolne przeciągnięcie
static const int SLOW_MS    = 30;  // pauza między krokami wolnego przeciągnięcia

// Ustawia parę A (STL+SBR) na offset a, parę B (STR+SBL) na offset b.
// Offset dodatni = noga do przodu (tak jak w turnLeft/turnRight).
static void pose(int a, int b){
  setAll(CENTER_STL + a, CENTER_STR + b,
         CENTER_SBL + b, CENTER_SBR + a);
}

static void pairPose(bool pairA, int off){
  if (pairA) pose(off, 0);
  else       pose(0, off);
}

// dir = +1 do przodu, -1 do tyłu
static void crawlHalf(bool pairA, int dir){
  int reach = dir * FWD * REACH;

  pairPose(pairA, reach);                    // 1. szybki wyrzut stóp do przodu
  delay(FAST_MS);

  for (int i = 1; i <= SLOW_STEPS; i++) {    // 2. wolne przeciągnięcie do tyłu
    int off = reach - (2 * reach * i) / SLOW_STEPS;
    pairPose(pairA, off);
    delay(SLOW_MS);
  }

  pairPose(pairA, 0);                        // 3. szybki powrót na środek
  delay(FAST_MS);
}

static void crawl(int dir){
  crawlHalf(true,  dir);   // przekątna STL + SBR
  crawlHalf(false, dir);   // przekątna STR + SBL
}

void stepForward(){
  crawl(+1);
}

void stepBackward(){
  crawl(-1);
}


void turnLeft(){
  setAll(CENTER_STL - STEP, CENTER_STR + STEP,
         CENTER_SBL - STEP, CENTER_SBR + STEP);
  delay(150);
  centerAll();
  delay(150);
}

void turnRight(){
  setAll(CENTER_STL + STEP, CENTER_STR - STEP,
         CENTER_SBL + STEP, CENTER_SBR - STEP);
  delay(150);
  centerAll();
  delay(150);
}

void sleep(){
setAll(MAX_A, MAX_A, MIN_A, MIN_A);
  delay(1000);
}

void chill(){
setAll(MAX_A, MAX_A, MIN_A, MIN_A);
  delay(1000);
}

float readBatteryVoltage() {
  int raw = analogRead(PIN_VBAT);

  float vpin = raw * (1.1 / 1023.0);
  return vpin * 7.666;
}