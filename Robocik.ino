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
    blink();
  }

  FrontLeft.attach(PIN_STL);
  FrontRight.attach(PIN_STR);
  BackLeft.attach(PIN_SBL);
  BackRight.attach(PIN_SBR);

  FrontLeft.write(CENTER_STL);
  FrontRight.write(CENTER_STR);
  BackLeft.write(CENTER_SBL);
  BackRight.write(CENTER_SBR);

  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  pinMode(PIN_BUTTON, INPUT);

  WallE_Hello();
  neutral(); 
}

void loop() {

static bool lastButton = LOW;
  bool button = digitalRead(PIN_BUTTON);

if (lastButton == LOW && button == HIGH) {
    chill();
    for(int i = 0; i<2; i++){
      blink();
      delay(700);
      }
    centerAll();
}
lastButton = button;

if(readBatteryVoltage() <= 6.0){
  err();
}

 if (Serial.available() > 0) {     
      char data = Serial.read(); 
      switch(data) {
        case 'W': for(int i = 0; i < 15; i++) {walk();} break;
        case 'M': ImperialMarch();    break;
        case 'C': faceSleep(); sleep(); lullabyStar(); delay(3000); blink(); centerAll(); break;
        case 'Z': FrontLeft.write(90); FrontRight.write(90); BackLeft.write(90); BackRight.write(90); break;
        case 'T': blink(); delay(200); for(int i = 0; i<2; i++) MegalovaniaDance(); break;
      default: break;
      }
   }
   delay(50);
}




