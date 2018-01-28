#include <math.h>
#include "Arduino.h"

#define TAU (3.14159*2)





// controls:  freq, rate, duty_cycle, phase


class SinePWM {
  public:
    SinePWM() {
      freq         = 1000.0;
      rate         = 130.0;
      duty_cycle   = 1.0;
      phase        = 0.0;
      cur_time     = 0;
      last_rising  = 0;
      next_rising  = 0;
      next_falling = 0;
      aspect       = .763;
      cur_state    = low;
      set_edges();
    }


    void set_edges(void) {
      next_rising  = next_rising + (freq/rate) + (sin((next_rising/freq)*TAU+phase)*(freq/rate)*aspect);
      next_falling = next_rising + ((freq/rate) + sin((last_rising/freq)*TAU+phase)*(freq/rate)*aspect)*duty_cycle;
    }

    void tick(void) {
      if (cur_state == low) {
        if (cur_time >= next_rising) {
          digitalWrite(LED_BUILTIN, HIGH);
          last_rising = next_rising;
          cur_state = high;
        } 
        
      } else { 
        if (cur_time >= next_falling) {
          digitalWrite(LED_BUILTIN, LOW);
          cur_state = low;
          next_rising = cur_time;
          set_edges();
        }
        
      }
      cur_time += 1;
    }
   
    void new_edge(void) {
      next_rising = last_rising;
      set_edges();
    }

    void set_freq(float new_freq) {
      freq = new_freq;
      new_edge();
    }
    
    void set_rate(float new_rate) {
      rate = new_rate;
      new_edge();
    }
    
    void set_duty_cycle(float new_duty_cycle) {
      duty_cycle = new_duty_cycle;
      new_edge();
    }

    void set_phase(float new_phase) {
      phase = new_phase;
      new_edge();
    }

  private:
    enum State { high, low };
    float freq;         // time units per full TAU cycle
    float rate;         // number of rising edges per TAU
    float duty_cycle;   // 0.0-1.0, percentage
    float phase;
    float aspect;
    unsigned int cur_time;
    unsigned int last_rising;
    unsigned int next_rising;
    unsigned int next_falling;
    State cur_state;
};




