/* DPlanterBoxMaster library

This class describes the "slave" side of the planter service (it is transport agnostic)
 
MIT license
written by Berto 'd Sera
*/

#ifndef DPlanterBoxMaster_h
#define DPlanterBoxMaster_h

#include "Arduino.h"
#include <DPlanterBox.h>


class DPlanterBoxMaster : public virtual DPlanterBox {      
  public:
    DPlanterBoxMaster();

    // input from hardware
    float soilHumidity(bool);
    bool  isConnected(bool);
    
    // output to hardware
    void  setGreen(bool,bool);
    void  setBlue(bool,bool); 
    void  setRed(bool,bool); 
};

#endif


