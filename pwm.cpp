#include <math.h>
#include <stdio.h>
#include <iostream>

#define TAU (3.14159*2)

using namespace std;

unsigned int cur_time = 0;



class SinePWM {
  public:
    SinePWM() {
      freq        = 500.0;
      rate        = 20.0;
      duty_cycle  = 0.5;
      phase       = 0.0;
      cur_time    = 0;
      last_change = 0;
      next_change = 0;
      cur_state   = low;
    }

    float next_rising_edge(void) {
      return last_change + ((freq/rate) + (sin((last_change/freq)*TAU+phase)*(freq/rate)));
    }

    float next_falling_edge(void) {
      return last_change + (((freq/rate) + (sin((last_change/freq)*TAU+phase)*(freq/rate)))*duty_cycle);
    }

    void tick(void) {
      cout << "tick" << endl;
      if (cur_time >= next_change) {
        last_change = cur_time;
        if(cur_state == low) {
          cur_state = high;
          next_change = next_rising_edge();
          cout << "rising edge " << next_change << endl;
        } else {
          cur_state = low;
          next_change = next_falling_edge();
          cout << "falling edge " << next_change << endl;
        }
      }
      cur_time += 1;
    }
  
  private:
    enum State { high, low };
    float freq;         // time units per full TAU cycle
    float rate;         // number of rising edges per TAU
    float duty_cycle;   // 0.0-1.0, percentage
    float phase;
    unsigned int cur_time;
    unsigned int last_change;
    unsigned int next_change;
    State cur_state;
};



int main(void) {
  SinePWM pwm;
  for(int i=0;i<500;i++) {
    pwm.tick();
  }
}
