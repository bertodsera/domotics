/* DistributedPlanterBoxMaster library

This class describes the "slave" side of the planter service (it is transport agnostic)
 
MIT license
written by Berto 'd Sera
*/

#ifndef DistributedPlanterBoxMaster_h
#define DistributedPlanterBoxMaster_h

#include "Arduino.h"
#include <DistributedPlanterBox.h>


class DistributedPlanterBoxMaster : public virtual DistributedPlanterBox {      
  public:
    DistributedPlanterBoxMaster();

    // input from hardware
    float soilHumidity(bool);
    bool  isConnected(bool);
    
    // output to hardware
    void  setGreen(bool,bool);
    void  setBlue(bool,bool); 
    void  setRed(bool,bool); 
};

#endif


