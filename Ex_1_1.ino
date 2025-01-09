#include "loopTimer.h"
#define LEDPIN 6

void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600);

}
void loop() {
  blinkLed();
  loopTimer.check(Serial);
}

void blinkLed(){
    digitalWrite(LEDPIN, HIGH); // turn on the LED
    delay(1000);  // wait for 1s
    digitalWrite(LEDPIN, LOW);  // turn off the LED
    delay(800);
    digitalWrite(LEDPIN, HIGH);
    delay(400);
    digitalWrite(LEDPIN, LOW);
    delay(200);
}
