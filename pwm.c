#define TAU 3.14159*2

float freq;     // time units per full TAU cycle
float rate;     // number of rising edges per TAU
float width;
float phase;

unsigned int cur_time = 0;
unsigned int last_rise = 0;

unsigned int next_rising_edge(void) {
  return last_rise + ((freq/rate) + sin(fmod(freq, last_rise)*TAU)*(freq/rate));
}
