/* PollingSensor library

This library implements a gemeric "polling sensor" that has
 1) an analog pin it inherits
 2) an attached digital pin that drives a PN2222 transitor that switches the sensor ON
 3) a label used for reporting
 4) a number of reads to be obtained and averaged, to reach a more stable sempling
 5) a bracket of min-max oscillation in the analog read (which is converted into a % value)
 
This is especially useful to 
   1) save the life of sensors that are "consumed by usage"
   2) minimize electric consumption
   3) minimize any possible impact on the polled medium (tipically soil, water, etc) 

MIT license
written by Berto 'd Sera
*/

#ifndef PollingSensor_h
#define PollingSensor_h

#include "Arduino.h"
#include <AnalogPin.h>
#include <DigitalPin.h>

class PollingSensor: public AnalogPin {
  private:
    String     label;    
    DigitalPin *driver;    
    int        topValue;
    int        bottomValue;
    float      conversionFactor;       
    int        repeatReads;
    float      lastLevel;   
    void       poll(void);
  public:
    PollingSensor(String, const uint8_t&, int, int, int, int);  
    float level(bool);
};

#endif