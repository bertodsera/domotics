/* DistributedPlanterBoxSlave library

This class describes the "slave" side of the planter service 
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DistributedPlanterBox.h>
#include <DistributedPlanterBoxSlave.h>
#include <PollingSensor.h>
#include <SoilHumiditySensor.h>

#define DP_CONNECTED_R 2
#define DP_CONNECTED_L 3
#define DP_SENSPWR_R 4
#define DP_SENSPWR_L 5
#define DP_RED_R 6
#define DP_RED_L 7
#define DP_GREEN_R 8
#define DP_GREEN_L 9
#define DP_BLUE_R 10
#define DP_BLUE_L 11
#define DP_BUZZER 12
#define AP_HUMSENS_R A0
#define AP_HUMSENS_L A1

DistributedPlanterBoxSlave::DistributedPlanterBoxSlave() 
  : DistributedPlanterBox::DistributedPlanterBox() {
  // right box connected pin
  connected[PLANTER_R].set_id(DP_CONNECTED_R);
  connected[PLANTER_R].setRead();  
  // left box connected pin
  connected[PLANTER_L].set_id(DP_CONNECTED_L);
  connected[PLANTER_L].setRead();
  
  // right box red LED
  redLED[PLANTER_R].set_id(DP_RED_R);
  redLED[PLANTER_R].setWrite();
  redLED[PLANTER_R].writeLow();
  // left box red LED
  redLED[PLANTER_L].set_id(DP_RED_L);
  redLED[PLANTER_L].setWrite();
  redLED[PLANTER_L].writeLow(); 
  
  // right box green LED
  greenLED[PLANTER_R].set_id(DP_GREEN_R);
  greenLED[PLANTER_R].setWrite();
  greenLED[PLANTER_R].writeLow();
  // left box green LED
  greenLED[PLANTER_L].set_id(DP_GREEN_L);
  greenLED[PLANTER_L].setWrite();
  greenLED[PLANTER_L].writeLow();
  
  // right box blue LED
  blueLED[PLANTER_R].set_id(DP_BLUE_R);
  blueLED[PLANTER_R].setWrite();
  blueLED[PLANTER_R].writeLow();
  // left box blue LED
  blueLED[PLANTER_L].set_id(DP_BLUE_L);
  blueLED[PLANTER_L].setWrite();
  blueLED[PLANTER_L].writeLow();
  
  // init sensors
  humiditySensor[PLANTER_R] = new SoilHumiditySensor("Right", AP_HUMSENS_R, DP_SENSPWR_R);
  humiditySensor[PLANTER_L] = new SoilHumiditySensor("Left", AP_HUMSENS_L, DP_SENSPWR_L);
}
    
    
// encode/decode data    
void DistributedPlanterBoxSlave::updateSoilHumidity(bool _side) {
  int i = index(_side);
  
  // update the sensor only if requested 
  //   (the master sets the timing between reads)
  if (((map.box[i].pins & REFRESH_PIN) == REFRESH_PIN) & (!errorState(_side) )) {
    // switch on signal
    blueLED[i].writeHigh();    
    
    // get a stable reading
    map.box[i].humidity = humiditySensor[i]->level(true);
    
    // switch off signal
    blueLED[i].writeLow();
  }  
  else {
    Serial.println(F("Bypassed update"));
    map.box[i].humidity = humiditySensor[i]->level(false);
  }
}


void DistributedPlanterBoxSlave::update(void) {
  updateConnected(true);
  updateConnected(false);
  updateOk(true);
  updateOk(false);
  updateError(true);
  updateError(false);
  updateSoilHumidity(true);
  updateSoilHumidity(false);
}


bool DistributedPlanterBoxSlave::errorState(bool _side) {
  int i = index(_side);
  return ((map.box[i].pins & ERROR_PIN) != 0); 
}


void DistributedPlanterBoxSlave::updatePin(bool _side, const int _mask, bool _on) {
  int i = index(_side);
  if (_on) { 
    map.box[i].pins = map.box[i].pins | _mask; 
  }
  else { 
    map.box[i].pins = map.box[i].pins & ~_mask; 
  }
}


void DistributedPlanterBoxSlave::updateConnected(bool _side) {
  bool state = connected[index(_side)].isSet();
  
  updatePin(_side, CONNECTED_PIN, state);
  if (state) {
    redLED[index(_side)].writeLow(); 
    greenLED[index(_side)].writeHigh();     
  }
  else {
    redLED[index(_side)].writeHigh(); 
    greenLED[index(_side)].writeLow();     
  }
} 


void DistributedPlanterBoxSlave::updateOk(bool _side) {
  bool state = connected[index(_side)].isSet();  
  updatePin(_side, OK_PIN, state);  
}    
    
void DistributedPlanterBoxSlave::updateWater(bool _side, bool _on) {
  updatePin(_side, WATER_PIN, _on); 
}

void DistributedPlanterBoxSlave::updateError(bool _side) {
  bool state = connected[index(_side)].isSet();   
  updatePin(_side, ERROR_PIN, !state); 
}

