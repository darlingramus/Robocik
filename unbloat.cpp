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
