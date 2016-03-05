/* Digital Pin library

MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DigitalPin.h>


DigitalPin::DigitalPin(void) 
  : GenericPin() { }

DigitalPin::DigitalPin(const uint8_t& _a) 
  : GenericPin(_a) { }


bool DigitalPin::isSet(void) {

  if (active()) {
    setWrite();
    writeLow();
    delay(20);
    setRead();
    delay(200);

    if (digitalRead(pin) == HIGH) { return true; }
  }

  return false;
}

bool DigitalPin::isOutput(void) {
  if ( DDRD & _BV(4) ) {   // Check bit #4 of the data direction register for port D
    // If we get here, then Arduino digital pin #4 was in output mode
    return true;
  } else {
    // If we get here, then Arduino digital pin #4 was in input mode
    return false;
  }
}

void DigitalPin::writeLow(void) {
  if (active()) {
    digitalWrite(pin, LOW);
  }
}


void DigitalPin::writeHigh(void) {
  if (active()) {
    digitalWrite(pin, HIGH);
  }
}
