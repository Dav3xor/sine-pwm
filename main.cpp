#include "pwm.hpp"

using namespace std;

int main(void) {
  SinePWM pwm;
  for(int i=0;i<500;i++) {
    pwm.tick();
  }
}
