/* Analog Pin library

MIT license
written by Berto 'd Sera
*/

#ifndef AnalogPin_h
#define AnalogPin_h

#include <GenericPin.h>

// wrapper for analog pins
class AnalogPin: public GenericPin {
  public:
    AnalogPin();    
    AnalogPin(const uint8_t&);
    float value(void);
    float stableValue(unsigned int);
};

#endif

