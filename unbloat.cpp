#include "unbloat.h"


Servo FrontLeft, FrontRight, BackLeft, BackRight;

int clampAngle(int a) {
  if (a < MIN_A) return MIN_A;
  if (a > MAX_A) return MAX_A;
  return (int)a;
}

// Ustawia pozycje z uwzględnieniem kierunku montażu
void setAll(byte stl, byte str, byte sbl, byte sbr) {
  FrontLeft.write(clampAngle(CENTER_STL + DIR_STL * (stl - CENTER_STL)));
  FrontRight.write(clampAngle(CENTER_STR + DIR_STR * (str - CENTER_STR)));
  BackLeft.write(clampAngle(CENTER_SBL + DIR_SBL * (sbl - CENTER_SBL)));
  BackRight.write(clampAngle(CENTER_SBR + DIR_SBR * (sbr - CENTER_SBR)));
}

void centerAll(){
  FrontLeft.write(CENTER_STL);
  FrontRight.write(CENTER_STR);
  BackLeft.write(CENTER_SBL);
  BackRight.write(CENTER_SBR);
}

//dzieki deepseekowi udalo sie zrobic tak by sie ruszał 

// Parametry do dostrojenia
static const int FWD        = +1;  // jeśli robot jedzie do tyłu zamiast do przodu -> zmień na -1
static const int REACH      = STEP; // wychył nogi od środka (stopnie)
static const int FAST_MS    = 70;  // czas szybkich ruchów (wyrzut / powrót)
static const int SLOW_STEPS = 8;   // na ile kroków dzielimy wolne przeciągnięcie
static const int SLOW_MS    = 30;  // pauza między krokami wolnego przeciągnięcia


static void pose(int a, int b){
  setAll(CENTER_STL + a, CENTER_STR + b,
         CENTER_SBL + b, CENTER_SBR + a);
}

static void pairPose(bool pairA, int off){
  if (pairA) pose(off, 0);
  else       pose(0, off);
}

static void crawlHalf(bool pairA, int dir){
  if (stopFlag) return;

  int reach = dir * FWD * REACH;

  pairPose(pairA, reach);    
  delay(FAST_MS);

  for (int i = 1; i <= SLOW_STEPS; i++) {  
    if (stopFlag) return;
    int off = reach - (2 * reach * i) / SLOW_STEPS;
    pairPose(pairA, off);
    delay(SLOW_MS);
  }

  if (stopFlag) return;
  pairPose(pairA, 0);                
  delay(FAST_MS);
}

static void crawl(int dir){
  crawlHalf(true,  dir);   
  crawlHalf(false, dir);   
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
setAll(20, MAX_A, 160, MIN_A);
  delay(1000);
}

void chill(){
setAll(20, MAX_A, 160, MIN_A);
  delay(1000);
}

float readBatteryVoltage() {
  int raw = analogRead(PIN_VBAT);

  float vpin = raw * (1.1 / 1023.0);
  return vpin * 7.666;
}


void setLegs(byte fl, byte fr, byte bl, byte br) {
  FrontLeft.write(fl);
  FrontRight.write(fr);
  BackLeft.write(bl);
  BackRight.write(br);
}

void neutral() {
  setLegs(CENTER_STL, CENTER_STR, CENTER_SBL, CENTER_SBR);
}

void walk() {
  // Krok 1: unosimy FrontLeft + BackRight
  setLegs(CENTER_STL - LIFT, CENTER_STR,
          CENTER_SBL,        CENTER_SBR - LIFT);
  delay(STEP_HOLD);

  // Krok 2: neutral
  neutral();
  delay(STEP_PAUSE);

  // Krok 3: unosimy FrontRight + BackLeft
  setLegs(CENTER_STL,        CENTER_STR - LIFT,
          CENTER_SBL - LIFT, CENTER_SBR);
  delay(STEP_HOLD);

  // Krok 4: neutral
  neutral();
  delay(STEP_PAUSE);
}

void dance() {
  for (int i = 0; i < 4; i++) {
    // Podskok na przednich nogach
    setLegs(CENTER_STL - 30, CENTER_STR - 30, CENTER_SBL, CENTER_SBR);
    delay(200);
    // Podskok na tylnych nogach
    setLegs(CENTER_STL, CENTER_STR, CENTER_SBL - 30, CENTER_SBR - 30);
    delay(200);
  }
  centerAll();
}

void happyDance() {
  tone(PIN_BUZZER, NOTE_E4, 150); delay(200);
  tone(PIN_BUZZER, NOTE_E4, 150); delay(200);
  tone(PIN_BUZZER, NOTE_G4, 150); delay(200);
  tone(PIN_BUZZER, NOTE_E4, 150); delay(200);
  
  tone(PIN_BUZZER, NOTE_D4, 150); delay(200);
  tone(PIN_BUZZER, NOTE_D4, 150); delay(200);
  tone(PIN_BUZZER, NOTE_C4, 300); delay(350);
  
  // Powtórka
  tone(PIN_BUZZER, NOTE_E4, 150); delay(200);
  tone(PIN_BUZZER, NOTE_E4, 150); delay(200);
  tone(PIN_BUZZER, NOTE_G4, 150); delay(200);
  tone(PIN_BUZZER, NOTE_E4, 150); delay(200);
  
  tone(PIN_BUZZER, NOTE_D4, 150); delay(200);
  tone(PIN_BUZZER, NOTE_D4, 150); delay(200);
  tone(PIN_BUZZER, NOTE_C4, 300); delay(350);
  
  noTone(PIN_BUZZER);
}