#pragma once

#include <Servo.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

extern Servo FrontLeft, FrontRight, BackLeft, BackRight;
extern volatile bool stopFlag;

// Dzielnik napiecia
const byte PIN_VBAT = A3;

// Piny servo
const byte PIN_STL = A0;
const byte PIN_STR = A1;
const byte PIN_SBL = A2;
const byte PIN_SBR = 6;

// Centrowanie
const byte CENTER_STL = 90;
const byte CENTER_STR = 90;
const byte CENTER_SBL = 90;
const byte CENTER_SBR = 90;

// Basic UART
const byte rxPin = 2;
const byte txPin = 3;

// "bezpieczne" katy (ostateczny kat wyslany do serwa)
const byte MIN_A = 5;
const byte MAX_A = 175;

// Kierunek montazu serw.
// Wychylenie logiczne x > 0 = taki obrot, przy ktorym przednie nogi ida W GORE,
// a tylne W DOL (u Ciebie: FL=20, FR=160, BL=20, BR=160).
// Lewe i prawe serwa sa lustrzane, dlatego znaki sa rozne.
const int8_t DIR_STL = -1;
const int8_t DIR_STR = +1;
const int8_t DIR_SBL = -1;
const int8_t DIR_SBR = +1;

// Buzzer
const byte PIN_BUZZER = 8;

// TTP223
const byte PIN_BUTTON = 4;

// ---------- Ustawienia chodu (tu dostrajasz) ----------
const int8_t GAIT_FWD     = +1;  // robot jedzie do tylu zamiast do przodu -> zmien na -1
const byte   GAIT_REACH   = 15;  // wychyl nogi od srodka (stopnie) - mniej = delikatniej
const byte   GAIT_FAST_MS = 70;  // szybki wyrzut / powrot
const byte   GAIT_SLOW_STEPS = 8;
const byte   GAIT_SLOW_MS = 30;  // pauza miedzy krokami wolnego przeciagniecia

const byte STAND_F  = 80;        // stanie: o ile PRZEDNIE nogi obracaja sie od srodka w strone ziemi (wiecej = wyzej z przodu)
const byte STAND_B  = 60;        // stanie: o ile TYLNE nogi obracaja sie od srodka w strone ziemi
const byte POSE_A   = 35;        // wychyl w pozach sleep / chill (lezenie)
const byte WIGGLE_A = 20;        // wychyl w tancu 'X' (wokol pozycji stania)

// ---------- API ----------
int  clampAngle(int a);
void setLegs(int fl, int fr, int bl, int br); // wychylenia logiczne wzgledem srodka (stopnie)
void centerAll();             // = lezy (nogi poziomo)

// Stanie
bool moveLegs(int fl, int fr, int bl, int br, byte steps = 12, byte stepMs = 20); // plynny przejazd, przerywalny
bool standUp();               // plynnie wstaje; false = przerwano
bool ensureStanding();        // wstaje tylko jesli lezy
void standAll();              // natychmiast pozycja stania (male korekty)
void holdPose();              // po 'Y': jesli stoi -> pozycja stania, jesli lezy -> nic

// Przerwanie (komenda 'Y')
void pollSerial();            // czyta Serial: 'Y' ustawia stopFlag, reszta trafia do pendingCmd
bool shouldStop();            // pollSerial() + zwraca stopFlag
char takePending();           // komenda odebrana w trakcie ruchu (0 = brak)
bool waitMs(unsigned long ms);// delay() ktory da sie przerwac; false = przerwano

// Silnik chodu (nieblokujacy)
void gaitBegin(int8_t dirL, int8_t dirR, bool loopForever);
bool gaitUpdate();            // wolaj czesto; false = chod skonczony
void gaitStop();

void stepForward();
void stepBackward();
void turnLeft();
void turnRight();
void chill();
void sleep();
void wiggle();
float readBatteryVoltage();