#include "Arduino.h"
#include "pwm.cpp"



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  SinePWM pwm;
  while(1) {
    pwm.tick();
    delay(10);
  }
}



