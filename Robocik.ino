#include "unbloat.h"
#include "RobotBuzzer.h"
#include "RobotOled.h"

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  analogReference(INTERNAL);

  blink();

  FrontLeft.attach(PIN_STL);
  FrontRight.attach(PIN_STR);
  BackLeft.attach(PIN_SBL);
  BackRight.attach(PIN_SBR);
  
  centerAll();

  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  pinMode(PIN_BUTTON, INPUT);

  WallE_Hello();
}

void loop() {
  static bool lastButton = LOW;

  bool button = digitalRead(PIN_BUTTON);
  if (lastButton == LOW && button == HIGH) {
    sleep();
    blink(); delay(700);
    blink();
    centerAll();
  }
  lastButton = button;

  if (readBatteryVoltage() <= 6.0) {
     err(); 
  }

  if (Serial.available() > 0) {
    char data = Serial.read();
    switch (data) {
      case 'W': for (int i = 0; i < 15; i++) walk(); break;
      case 'M': ImperialMarch(); break;
      case 'C': faceSleep(); sleep(); lullabyStar(); delay(3000); blink(); centerAll(); break;
      case 'Z': centerAll(); break;
      case 'T': blink(); delay(200); for (int i = 0; i < 2; i++) MegalovaniaDance(); break;
    }
  }
  delay(50);
}