/* Actuator library
  
Basic Actuator:
  1) associated to a digitalPin
  2) has a cycle length
  3) has a minimal guaranteed sleep time between cycles

MIT license
written by Berto 'd Sera
*/

#ifndef Actuator_h
#define Actuator_h

#include "Arduino.h"
#include <Time.h>
#include <DigitalPin.h>

// A generic actuator
class Actuator: public DigitalPin {
  private:
    String  label; 
    time_t  lastTransition; 
    time_t  cycleLenghtSeconds;   
    time_t  minSleep;
    void    forceKill(void); 
  
  public:
    Actuator(int, time_t);
    void evaluate(void);
    void fire(void);
    void stop(void) 
};

#endif