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

  FrontLeft.attach(PIN_STL);
  FrontRight.attach(PIN_STR);
  BackLeft.attach(PIN_SBL);
  BackRight.attach(PIN_SBR);
  centerAll();                // na starcie lezy (nogi poziomo)

  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  pinMode(PIN_BUTTON, INPUT);

  WallE_Hello();
  standUp();                  // wstaje po powitaniu
}

void loop() {
  static bool lastButton = LOW;
  bool button = digitalRead(PIN_BUTTON);

  if (lastButton == LOW && button == HIGH) {
    faceChill();
    chill();
    faceHappy();
    standUp();
  }
  lastButton = button;

  // if(readBatteryVoltage() <= 6.0){
  //   err();
  //   tone(PIN_BUZZER, 200, 500);
  // }

  if (stopFlag) {             // 'Y' zlapane w trakcie ruchu przez pollSerial()
    stopFlag = false;
    noTone(PIN_BUZZER);
    holdPose();
    faceHappy();
  }

  char data = takePending();  // komenda odebrana w trakcie poprzedniego ruchu
  if (data == 0 && Serial.available() > 0) {
    data = Serial.read();
  }

  if (data != 0) {
    if (data == 'Y') {
      noTone(PIN_BUZZER);
      holdPose();
      faceHappy();
    }

    stopFlag = false;

    switch (data) {
      case 'W': stepForward();  break;
      case 'S': stepBackward(); break;
      case 'A': turnLeft();     break;
      case 'D': turnRight();    break;
      case 'B': ImperialMarch(); break;
      case 'C': faceSleep(); sleep(); faceHappy(); break;
      case 'X': wiggle();       break;
      case 'Z': standUp();      break;
      case 'N': centerAll();    break;
      default:  break;
    }
  }

  delay(10);
}
