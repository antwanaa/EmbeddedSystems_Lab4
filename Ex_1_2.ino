#include "loopTimer.h"
#define BUZZER 5

void setup() {
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  buzz();
  loopTimer.check(Serial);
}

void buzz(){
  tone(BUZZER, 100); //Set the voltage to high and makes a noise
  delay(100);     //Waits for 1000 milliseconds
  noTone(BUZZER); //Sets the voltage to low and makes no noise
  delay(500);     //Waits for 500 milliseconds
}
