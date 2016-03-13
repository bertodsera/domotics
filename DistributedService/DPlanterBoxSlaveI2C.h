/* DPlanterBoxSlaveI2C library

This class describes the "slave" side of the pond 
 
MIT license
written by Berto 'd Sera
*/

#ifndef DPlanterBoxSlaveI2C_h
#define DPlanterBoxSlaveI2C_h

#include "Arduino.h"
#include <DPI2CSlave.h>
#include <DPlanterBoxSlave.h>


class DPlanterBoxSlaveI2C : public virtual DPI2CSlave {
    // actual actions triggered by the callbacks
    void slaveImplementGet(void);    
    void slavePrepareSend(void);     
  
  public:
    DPlanterBoxSlaveI2C(uint8_t); 
};








#endif
