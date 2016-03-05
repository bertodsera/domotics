/* DistributedPlanterBoxSlaveI2C library

This class implements the "slave" side of the planter service, on an I2C network 
 
MIT license
written by Berto 'd Sera
*/

#ifndef DistributedPlanterBoxSlaveI2C_h
#define DistributedPlanterBoxSlaveI2C_h

#include "Arduino.h"
#include <DistributedPlanterBoxSlave.h>
#include <DistributedServiceI2CSlave.h>


class DistributedPlanterBoxSlaveI2C : 
  public virtual DistributedPlanterBoxSlave,
  public virtual DistributedServiceI2CSlave  {   
  public:
    DistributedPlanterBoxSlaveI2C(uint8_t);
    void slaveImplementGet(void); 
};


#endif
