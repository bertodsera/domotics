/* Luxmetre library
  
A luxmetre sensor

MIT license
written by Berto 'd Sera
*/

#ifndef Luxmetre_h
#define Luxmetre_h

#include "Arduino.h"
#include <Time.h>
#include <TSL2561.h>

class Luxmetre {
  private:
    TSL2561  *sensor;
    time_t   lastReading;
    time_t   validity;
    double   infraredLightValue;
    double   visibleLightValue;
    double   luxValue;      
    void     refresh();
  public:
    Luxmetre(time_t);
    double infrared();
    double visible();    
    double full(); 
    double lux();     
};

#endif