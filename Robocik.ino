#include "unbloat.h"
#include "RobotBuzzer.h"
#include "RobotOled.h"

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(9600);
  Wire.begin();
  analogReference(INTERNAL);

if (!display.begin(0x3C, true)) {
    Serial.println(F("OLED fail"));
  } else {
    faceHappy();
  }

  STL.attach(PIN_STL);
  STR.attach(PIN_STR);
  SBL.attach(PIN_SBL);
  SBR.attach(PIN_SBR);

  STL.write(CENTER_STL);
  STR.write(CENTER_STR);
  SBL.write(CENTER_SBL);
  SBR.write(CENTER_SBR);

  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);

  pinMode(PIN_BUTTON, INPUT);
}

void loop() {

static bool lastButton = LOW;
  bool button = digitalRead(PIN_BUTTON);

if (lastButton == LOW && button == HIGH) {
    faceChill();
    chill();
    faceHappy();
    centerAll();
}

lastButton = button;

 if (Serial.available() > 0) {     
      char data = Serial.read(); 
      switch(data) {
        case 'W': stepForward();  break;
        case 'S': stepBackward(); break;
        case 'A': turnLeft();     break;
        case 'D': turnRight();    break;
        case 'B': ImperialMarch();    break;
        case 'C': faceSleep(); sleep(); faceHappy(); break;
      default: break;
      }
   }
   delay(50);

}
