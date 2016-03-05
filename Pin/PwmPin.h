/* PWM Pin library

These Pins are capable of setting an outward pulse, rather than just a stable hi/lo signal

MIT license
written by Berto 'd Sera
*/

#ifndef PwmPin_h
#define PwmPin_h

#include <DigitalPin.h>


// wrapper for digital pins with PWM
class PwmPin: public DigitalPin {
  public:
    PwmPin();    
    PwmPin(const uint8_t&);
    void setPulse(int);
};

#endif

