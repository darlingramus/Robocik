#include "RobotOled.h"

void showFace(const char* text, uint8_t size, int16_t x_offset) {
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setTextWrap(false);
  display.setTextSize(size);
  display.setCursor(x_offset, 4);
  display.print(text);
  display.setTextSize(1);
  display.setCursor(0, 56);
  display.print(readBatteryVoltage(), 1);
  display.print(F("V"));
  display.display();
}

void blink() {
  showFace("^v^", 7, 2); 
  delay(200);
  showFace("---", 7, 2); 
  delay(100);
  showFace(">v<", 7, 2);
}
void faceHappy() { showFace(">v<", 7, 2); }
void faceChill() { showFace(">..<", 5, 4); }
void faceSleep() { showFace("-_-", 7, 2); }
void err() { showFace("err", 7, 2); }