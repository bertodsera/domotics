/* SoilHumiditySensor library

MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <PollingSensor.h>
#include <SoilHumiditySensor.h>


SoilHumiditySensor::SoilHumiditySensor(String name, const uint8_t& _an, int _di) 
    : PollingSensor(name, _an, _di, 100, 510, 0) {
      // 100 reads averaged
      // 510 max value
      // 40 min value
}


