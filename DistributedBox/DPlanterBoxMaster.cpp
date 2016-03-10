/* DPlanterBoxMaster library

This class describes the "master" side of the planter service 
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DPlanterBox.h>
#include <DPlanterBoxMaster.h>


    
// encode/decode data    
float DPlanterBoxMaster::soilHumidity(bool _side) {
  return map.box[index(_side)].humidity;
}


bool DPlanterBoxMaster::isConnected(bool _side) {
  return ((map.box[index(_side)].pins & CONNECTED_PIN) == CONNECTED_PIN);
}


void DPlanterBoxMaster::setGreen(bool _side, bool _value) {
  
}


void DPlanterBoxMaster::setBlue(bool _side, bool _value) {
  
}


void DPlanterBoxMaster::setRed(bool _side, bool _value) {
  
}
    