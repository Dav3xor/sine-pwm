#include "Arduino.h"
#include "pwm.cpp"


int cur_rate;
int prev_rate;
SinePWM pwm;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  cur_rate = analogRead(A0);
  prev_rate = 0;
}

void loop() {

  while(1) {
    //Serial.println(analogRead(A0));
    cur_rate += ((analogRead(A0)-cur_rate)/8);
    if (cur_rate != prev_rate) {
      Serial.print(prev_rate);
      Serial.print("-");
      Serial.println(cur_rate);
      pwm.set_rate(analogRead(A0));
      prev_rate = cur_rate;
    }
    //pwm.set_duty_cycle(.5);
    pwm.tick();
    delay(20);
  }
}



