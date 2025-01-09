#include "loopTimer.h"
#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
#define LEDPIN 6
#define BUZZER 5

int buzzerState = 0;
unsigned long buzzerTime = 0;
int ledState = 0;
unsigned long ledTime = 0;
int screenState = 0;
unsigned long screenTime = 0;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
  u8x8.begin();       // to start using the screen
  u8x8.setFlipMode(1);
}

void loop() {
  loopTimer.check(Serial);
  unsigned long times = millis();
  if(times >= ledTime){ // if it is time to toggle the LED then go into function
    ledTask();
  }
  if(times >= buzzerTime){ // if it is time to toggle the buzzer then go into function
    buzzTask();
  }
  if(times >= screenTime){  // if it is time to toggle the screen then go into function
    messageTask();
  }
}

// set a timer for next time a change needs to be made to the LED. then make a change (turn on or off)
void ledTask(){
  Serial.println("Task 1 Running");
  if(ledState == 0){
    ledTime = millis() + 500;
    ledState = 1;
    digitalWrite(LEDPIN, HIGH);
  }else{
    ledTime = millis() + 1000;
    ledState = 0;
    digitalWrite(LEDPIN, LOW);
  }
}

// set a timer for next time a change needs to be made to the buzzer. then make a change (turn on or off)
void buzzTask(){
  Serial.println("Task 2 Running");
  if(buzzerState == 1){
    buzzerTime = millis() + 500;
    buzzerState = 0;
    noTone(BUZZER); //Sets the voltage to low and makes no noise
  }else{
    buzzerTime = millis() + 100;
    buzzerState = 1;
    tone(BUZZER, 100); //Set the voltage to high and makes a noise
  }
}

// set a timer for next time a change needs to be made to the screen. then make a change (turn on or off)
void messageTask(){
  Serial.println("Task 3 Running");
  if(screenState == 1){
    screenTime = millis() + 500;
    screenState = 0;
    u8x8.clear();
  }else{
    screenTime = millis() + 1000;
    screenState = 1;
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.setCursor(0, 4);   //defining the starting point for the cursor
    u8x8.print("Hello World");  // Print "Hello World" on the display
  }
}
