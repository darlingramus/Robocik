#include "unbloat.h"

Servo FrontLeft, FrontRight, BackLeft, BackRight;
volatile bool stopFlag = false;

static char pendingCmd = 0;
static bool standing = false;
static int cur[4] = {0, 0, 0, 0};   // ostatnie wychylenia logiczne (do plynnych przejazdow)

int clampAngle(int a) {
  if (a < MIN_A) return MIN_A;
  if (a > MAX_A) return MAX_A;
  return a;
}

// Wychylenia logiczne wzgledem srodka (x > 0 = przod w gore / tyl w dol) -> katy serw
void setLegs(int fl, int fr, int bl, int br) {
  cur[0] = fl; cur[1] = fr; cur[2] = bl; cur[3] = br;
  FrontLeft.write(clampAngle(CENTER_STL + DIR_STL * fl));
  FrontRight.write(clampAngle(CENTER_STR + DIR_STR * fr));
  BackLeft.write(clampAngle(CENTER_SBL + DIR_SBL * bl));
  BackRight.write(clampAngle(CENTER_SBR + DIR_SBR * br));
}

void centerAll() {
  setLegs(0, 0, 0, 0);
}

// Wychylenia wzgledem pozycji STANIA: przednie nogi -STAND_F, tylne +STAND_B (obie strony ku ziemi)
static void setStance(int fl, int fr, int bl, int br) {
  setLegs(fl - STAND_F, fr - STAND_F, bl + STAND_B, br + STAND_B);
}

// ================== PRZERWANIE ==================
// Serial ma bufor wypelniany przez przerwanie sprzetowe, wiec wystarczy
// regularnie go oprozniac - robimy to w kazdym oczekiwaniu i w kazdej petli ruchu.
void pollSerial() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'Y') {
      stopFlag = true;
      pendingCmd = 0;            // wszystko co przyszlo przed 'Y' jest anulowane
    } else if (c > ' ') {        // ignoruj \r \n spacje
      pendingCmd = c;            // ostatnia komenda wygrywa (kolejka sie nie zapycha)
    }
  }
}

bool shouldStop() {
  pollSerial();
  return stopFlag;
}

char takePending() {
  char c = pendingCmd;
  pendingCmd = 0;
  return c;
}

bool waitMs(unsigned long ms) {
  unsigned long t0 = millis();
  while (millis() - t0 < ms) {
    if (shouldStop()) return false;
  }
  return !shouldStop();
}

// ================== STANIE / LEZENIE ==================
bool moveLegs(int fl, int fr, int bl, int br, byte steps, byte stepMs) {
  int to[4] = {fl, fr, bl, br};
  int from[4] = {cur[0], cur[1], cur[2], cur[3]};
  for (byte i = 1; i <= steps; i++) {
    setLegs(from[0] + (to[0] - from[0]) * i / steps,
            from[1] + (to[1] - from[1]) * i / steps,
            from[2] + (to[2] - from[2]) * i / steps,
            from[3] + (to[3] - from[3]) * i / steps);
    if (!waitMs(stepMs)) return false;
  }
  return true;
}

void standAll() {
  setStance(0, 0, 0, 0);
  standing = true;
}

bool standUp() {
  if (!moveLegs(-STAND_F, -STAND_F, STAND_B, STAND_B, 15, 25)) return false;
  standing = true;
  return true;
}

bool ensureStanding() {
  return standing ? true : standUp();
}

void holdPose() {
  if (standing) standAll();
}

// ================== CHOD ==================
// Dwie pary diagonalne: A = (FL, BR), B = (FR, BL).
// Kazda polowka cyklu jednej pary: szybki wyrzut do przodu -> wolne przeciagniecie
// do tylu (to popycha robota) -> szybki powrot do pozycji stania. Druga para stoi.
// Lewe i prawe nogi maja osobny kierunek (dirL/dirR) - dzieki temu ten sam silnik
// robi chod do przodu, do tylu i skrety.

static const byte GAIT_LAST = GAIT_SLOW_STEPS + 1;   // idx: 0=wyrzut, 1..N=przeciagniecie, N+1=powrot

static int8_t gDirL = 1, gDirR = 1;
static bool gActive = false, gLoop = false, gHalfB = false;
static byte gIdx = 0;
static unsigned long gNextAt = 0;

static int strokePos(byte idx) {
  const int reach = GAIT_FWD * GAIT_REACH;
  if (idx == 0) return reach;
  if (idx <= GAIT_SLOW_STEPS) return reach - (2 * reach * idx) / GAIT_SLOW_STEPS;
  return 0;
}

static unsigned long gaitDur(byte idx) {
  return (idx == 0 || idx == GAIT_LAST) ? GAIT_FAST_MS : GAIT_SLOW_MS;
}

static void gaitApply() {
  int p = strokePos(gIdx);
  int l = gDirL * p;
  int r = gDirR * p;
  if (!gHalfB) setStance(l, 0, 0, r);   // para A: FL + BR
  else         setStance(0, r, l, 0);   // para B: FR + BL
}

void gaitBegin(int8_t dirL, int8_t dirR, bool loopForever) {
  gDirL = dirL;
  gDirR = dirR;
  gLoop = loopForever;
  gHalfB = false;
  gIdx = 0;
  gActive = true;
  gaitApply();
  gNextAt = millis() + gaitDur(gIdx);
}

static void gaitAdvance() {
  if (gIdx < GAIT_LAST) {
    gIdx++;
  } else {
    gIdx = 0;
    if (!gHalfB) {
      gHalfB = true;
    } else {
      gHalfB = false;
      if (!gLoop) {            // pelny cykl zakonczony, nogi sa w pozycji stania
        gActive = false;
        return;
      }
    }
  }
  gaitApply();
  gNextAt = millis() + gaitDur(gIdx);
}

bool gaitUpdate() {
  if (!gActive) return false;
  if ((long)(millis() - gNextAt) >= 0) gaitAdvance();
  return gActive;
}

void gaitStop() {
  gActive = false;
  standAll();
}

// Jeden pelny cykl (obie pary), przerywalny; najpierw wstaje jesli lezy
static void crawlCycle(int8_t dirL, int8_t dirR) {
  if (!ensureStanding()) return;
  gaitBegin(dirL, dirR, false);
  while (gaitUpdate()) {
    if (shouldStop()) {
      gaitStop();
      return;
    }
  }
}

void stepForward()  { crawlCycle(+1, +1); }
void stepBackward() { crawlCycle(-1, -1); }
// skret w lewo: prawe nogi pchaja do przodu, lewe do tylu (i odwrotnie)
void turnLeft()     { crawlCycle(-1, +1); }
void turnRight()    { crawlCycle(+1, -1); }

// ================== POZY ==================
// Poza lezaca (kladzie sie i zostaje lezec do nastepnej komendy ruchu)
static void lieDown() {
  standing = false;
  moveLegs(POSE_A, POSE_A, -POSE_A, -POSE_A, 15, 25);
  waitMs(1000);
}

void sleep() { lieDown(); }
void chill() { lieDown(); }

// dawne 'X' - ta sama sekwencja, ale wokol pozycji stania i z mniejszym wychylem
void wiggle() {
  if (!ensureStanding()) return;
  int f = 0, b = 0;
  for (int i = 0; i < 5; i++) {
    f =  WIGGLE_A; setStance(f, f, b, b); if (!waitMs(200)) break;
    b =  WIGGLE_A; setStance(f, f, b, b); if (!waitMs(200)) break;
    f = -WIGGLE_A; setStance(f, f, b, b); if (!waitMs(200)) break;
    b = -WIGGLE_A; setStance(f, f, b, b); if (!waitMs(200)) break;
  }
  holdPose();
}

float readBatteryVoltage() {
  int raw = analogRead(PIN_VBAT);

  float vpin = raw * (1.1 / 1023.0);
  return vpin * 7.666;
}