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
      last_rising = 0;
      next_change = 0;
      cur_state   = high;
    }


    set_edges(void) {
      next_rising  = next_rising + (freq/rate) + (sin((next_rising/freq)*TAU+phase)*(freq/rate));
      next_falling = next_rising + ((freq/rate) + sin((last_rising/freq)*TAU+phase)*(freq/rate))*duty_cycle;
    }

    float next_rising_edge(void) {
      return last_rising + (freq/rate) + (sin((last_rising/freq)*TAU+phase)*(freq/rate));
    }

    float next_falling_edge(void) {
      return last_rising + (( (freq/rate) + (sin((last_rising/freq)*TAU+phase)*(freq/rate))*duty_cycle));
    }

    void tick(void) {
      cout << "tick" << endl;
      if (cur_time >= next_change) {
        if(cur_state == low) {
          cur_state = high;
          next_change = next_falling_edge();
          last_rising = cur_time;
          cout << "rising edge " << next_change << endl;
        } else {
          cur_state = low;
          next_change = next_rising_edge();
          cout << "falling edge " << next_change << endl;
        }
      }
      cur_time += 1;
    }
   
    void new_edge(void) {
      if(cur_state==low) {
        next_change = next_rising_edge();
      } else {
        next_change = next_falling_edge();
      }
    }

    void set_freq(float new_freq) {
      freq = new_freq;
      new_edge();
    }

  private:
    enum State { high, low };
    float freq;         // time units per full TAU cycle
    float rate;         // number of rising edges per TAU
    float duty_cycle;   // 0.0-1.0, percentage
    float phase;
    unsigned int cur_time;
    unsigned int last_rising;
    unsigned int next_change;
    State cur_state;
};



int main(void) {
  SinePWM pwm;
  for(int i=0;i<500;i++) {
    pwm.tick();
  }
}
