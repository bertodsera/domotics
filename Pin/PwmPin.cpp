/* PWM Pin library

These Pins are capable of setting an outward pulse, rather than just a stable hi/lo signal

MIT license
written by Berto 'd Sera
*/

#include <DigitalPin.h>
#include <PwmPin.h>

PwmPin::PwmPin(const uint8_t& _id)
  : DigitalPin(_id) { }

PwmPin::PwmPin()
  : DigitalPin() { }


void PwmPin::setPulse(int _value) {
  // set the pin as output before setting the pulse
  pinMode(pin, OUTPUT);   
  analogWrite(pin, _value);  
}
