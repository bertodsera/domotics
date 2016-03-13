/* DPlanterBoxSlave library

This class describes the "slave" side of the planter service (it is transport agnostic)

It can also be used to test the hardware of the "box"
 
MIT license
written by Berto 'd Sera
*/

#ifndef DPlanterBoxSlave_h
#define DPlanterBoxSlave_h

#include "Arduino.h"
#include <DPlanterBox.h>
#include <DigitalPin.h>
#include <AnalogPin.h>
#include <SoilHumiditySensor.h>


// TODO move green LEDs to PWM pins, so we can change level of luminosity, to reflect humidity
#define DP_CONNECTED_R 2
#define DP_CONNECTED_L 3 // PWM
#define DP_SENSPWR_R 4
#define DP_SENSPWR_L 5 // PWM
#define DP_RED_R 6 // PWM
#define DP_RED_L 7
#define DP_GREEN_R 8
#define DP_GREEN_L 9 // PWM
#define DP_BLUE_R 10 // PWM
#define DP_BLUE_L 11 // PWM
#define DP_BUZZER_L 12
#define AP_HUMSENS_R A0
#define AP_HUMSENS_L A1

class DPlanterBoxSlave : public virtual DPlanterBox {    
  private:
    void updatePin(bool, const int, bool);
    
  protected:
    // This needs a 10k pull-down resistor to ensure HIGH means SWITCH CLOSED
    //    see https://www.arduino.cc/en/Reference/Constants
    DigitalPin connected[2];
     
    DigitalPin redLED[2];  
    DigitalPin greenLED[2]; 
    DigitalPin blueLED[2]; 

    DigitalPin buzzer;     
    
    SoilHumiditySensor *humiditySensor[2];      
  public:
    DPlanterBoxSlave(void);
    
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
    void  buzz(int);
};

#endif


