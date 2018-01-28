#include "Arduino.h"
#include "pwm.cpp"

SinePWM pwm;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  while(1) {
    Serial.print(analogRead(A0));
    pwm.tick();
    delay(10);
  }
}



