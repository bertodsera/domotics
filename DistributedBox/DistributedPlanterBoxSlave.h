/* DistributedPlanterBoxSlave library

This class describes the "slave" side of the planter service (it is transport agnostic)
 
MIT license
written by Berto 'd Sera
*/

#ifndef DistributedPlanterBoxSlave_h
#define DistributedPlanterBoxSlave_h

#include "Arduino.h"
#include <DistributedPlanterBox.h>
#include <DigitalPin.h>
#include <AnalogPin.h>
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
#define AP_HUMSENS_R A0
#define AP_HUMSENS_L A1

class DistributedPlanterBoxSlave : public virtual DistributedPlanterBox {    
  private:
    void updatePin(bool, const int, bool);
    
  protected:
    // This needs a 10k pull-down resistor to ensure HIGH means SWITCH CLOSED
    //    see https://www.arduino.cc/en/Reference/Constants
    DigitalPin connected[2];
     
    DigitalPin redLED[2];  
    DigitalPin greenLED[2]; 
    DigitalPin blueLED[2];     
    
    SoilHumiditySensor *humiditySensor[2];      
  public:
    DistributedPlanterBoxSlave(void);
    
    // status
    bool errorState(bool);
    
    // input from hardware
    void  updateSoilHumidity(bool);    
    void  updateConnected(bool);
    
    // output to hardware
    void  update(void); 
    void  updateOk(bool);    
    void  updateWater(bool,bool);    
    void  updateError(bool);    
};

#endif


