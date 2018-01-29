#include "Arduino.h"
#include "pwm.cpp"

SinePWM pwm;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  while(1) {
    Serial.println(analogRead(A0));
    pwm.set_duty_cycle(analogRead(A0));
    pwm.tick();
    delay(200);
  }
}



