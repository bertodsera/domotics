/* DistributedPlanterBoxMaster library

This class describes the "master" side of the planter service 
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DistributedPlanterBox.h>
#include <DistributedPlanterBoxMaster.h>


    
// encode/decode data    
float DistributedPlanterBoxMaster::soilHumidity(bool _side) {
  return map.box[index(_side)].humidity;
}

bool DistributedPlanterBoxMaster::isConnected(bool _side) {
  return map.box[index(_side)].pins & CONNECTED_PIN;
}

void DistributedPlanterBoxMaster::setGreen(bool _side, bool _value) {
  
}

void DistributedPlanterBoxMaster::setBlue(bool _side, bool _value) {
  
}

void DistributedPlanterBoxMaster::setRed(bool _side, bool _value) {
  
}
    