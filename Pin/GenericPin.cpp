/* Generic Pin library

MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <GenericPin.h>

GenericPin::GenericPin(void) {
  pin = -1;
}


GenericPin::GenericPin(const uint8_t& a) {
  set_id(a);
}


int GenericPin::id(void) {
  return pin;
};


void GenericPin::set_id(const uint8_t& a) {
  pin = a;
};


bool GenericPin::active(void) {
  if (pin != -1) { return true; }
  return false;
}


void GenericPin::setRead(void) {
  if (active()) {
    pinMode(pin, INPUT);
  }
}


void GenericPin::setWrite(void) {
  if (active()) {
    pinMode(pin, OUTPUT);
  }
}

