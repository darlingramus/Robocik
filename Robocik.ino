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

  FrontLeft.write(CENTER_STL);
  FrontRight.write(CENTER_STR);
  BackLeft.write(CENTER_SBL);
  BackRight.write(CENTER_SBR);

  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);

  pinMode(PIN_BUTTON, INPUT);
}

void DDDDD(){

  FrontLeft.write(60);   // Lift leg
  FrontRight.write(90);  // Down
  BackLeft.write(90);    // Down
  BackRight.write(60);   // Lift leg
  delay(500);            // Hold position

  // Step 2: Return to neutral (all legs down)
  FrontLeft.write(90);
  FrontRight.write(90);
  BackLeft.write(90);
  BackRight.write(90);
  delay(200);            // Brief pause

  // Step 3: Lift front-right and back-left, lower others
  FrontLeft.write(90);   // Down
  FrontRight.write(60);  // Lift leg
  BackLeft.write(60);    // Lift leg
  BackRight.write(90);   // Down
  delay(500);            // Hold position

  // Step 4: Return to neutral (all legs down)
  FrontLeft.write(90);
  FrontRight.write(90);
  BackLeft.write(90);
  BackRight.write(90);
  delay(200);     
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
        case 'X': for(int i = 0; i < 5; i++){FrontLeft.write(20); FrontRight.write(160); delay(200); BackLeft.write(20); BackRight.write(160); delay(200);FrontLeft.write(160); FrontRight.write(20); delay(200); BackLeft.write(160); BackRight.write(20); delay(200);} break;
        case 'Z':   FrontLeft.write(90); FrontRight.write(90); BackLeft.write(90); BackRight.write(90); break;
      default: break;
      }
   }
   delay(50);

}
