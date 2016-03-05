/* Digital Pin library

MIT license
written by Berto 'd Sera
*/

#ifndef DigitalPin_h
#define DigitalPin_h

#include <GenericPin.h>


// wrapper for digital pins
class DigitalPin: public GenericPin {
  public:
    DigitalPin();    
    DigitalPin(const uint8_t&);
    bool isOutput(void);
    bool isSet(void);
    void writeLow(void);
    void writeHigh(void);
};

#endif

