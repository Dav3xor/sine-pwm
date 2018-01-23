#include <math.h>
#include <stdio.h>

#define TAU (3.14159*2)

float freq       = 500.0;     // time units per full TAU cycle
float rate       = 20.0;     // number of rising edges per TAU
float duty_cycle = 0.5;   // 0.0-1.0, percentage
float phase      = 0.0;

unsigned int cur_time = 0;
unsigned int last_rise = 0;

float next_rising_edge(void) {
  return last_rise + ((freq/rate) + (sin((last_rise/freq)*TAU+phase)*(freq/rate)));
}

float next_falling_edge(void) {
  return last_rise + (((freq/rate) + (sin((last_rise/freq)*TAU+phase)*(freq/rate)))*duty_cycle);
}

int main(void) {
  for(int i=0;i<500;i++) {
    printf("prev = %d next = %f\n", last_rise, next_rising_edge());
    last_rise+=1;
  }
  printf("%f\n", last_rise/freq);
}
