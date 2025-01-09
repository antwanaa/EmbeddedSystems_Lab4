#define LEDPIN 6

int ledStatus = 0;

void setup() {
  pinMode(LEDPIN, OUTPUT);

}
void loop() {
  blinkLed();
}

void blinkLed(){
  if(ledStatus == 0){
    ledStatus = 1;
    digitalWrite(LEDPIN, HIGH);
      delay(1000);
  }else if(ledStatus == 1){
    ledStatus = 2;
    digitalWrite(LEDPIN, LOW);{
    delay(800);
    }
  }else if(ledStatus == 2){
    ledStatus = 3;
    digitalWrite(LEDPIN, HIGH);{
    delay(400);
    }
  }else{
    ledStatus = 0;
    digitalWrite(LEDPIN, LOW);
    delay(200);
  }
}
