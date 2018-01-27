#include "pwm.hpp"

using namespace std;

int main(void) {
  SinePWM pwm;
  for(int i=0;i<2000;i++) {
    pwm.tick();
  }
}
