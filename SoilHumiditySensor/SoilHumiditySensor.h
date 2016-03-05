/* SoilHumiditySensor library

MIT license
written by Berto 'd Sera
*/

#ifndef SoilHumiditySensor_h
#define SoilHumiditySensor_h

#include "Arduino.h"
#include <PollingSensor.h>

class SoilHumiditySensor: public PollingSensor {
  public:
    SoilHumiditySensor(String, const uint8_t&, int);
};

#endif