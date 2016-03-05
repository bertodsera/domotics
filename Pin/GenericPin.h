/* GenericPin library

MIT license
written by Berto 'd Sera
*/

#ifndef GenericPin_h
#define GenericPin_h

#include "Arduino.h"

// any pin
class GenericPin {
  protected:
    int pin;
    bool active(void);

  public:
    GenericPin(void);
    GenericPin(const uint8_t&);
    int id(void);
    void set_id(const uint8_t&);
    void setRead(void);
    void setWrite(void);
};

#endif

