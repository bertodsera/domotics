/* Analog Pin library

MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <AnalogPin.h>

AnalogPin::AnalogPin(const uint8_t& a) 
  : GenericPin(a) { }

AnalogPin::AnalogPin(void) 
  : GenericPin() { }


float AnalogPin::value(void) {
  if (active()) {
    return analogRead(pin);
  }
  return 0.0;
}

float AnalogPin::stableValue(unsigned int cnt) {
  if (active()) {

    if (cnt > 1000) { cnt = 1000; }
    else {
      if (cnt == 0) { cnt = 1; }
    }

    // multiple samples to stabilize
    float v = 0.0;
    for (unsigned int i=0; i<cnt; i++) v += analogRead(pin);
    v = v / cnt;     // make average
    return v;
  }

  return 0.0;
}



