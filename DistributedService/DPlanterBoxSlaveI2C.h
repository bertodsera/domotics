/* DistributedPlanterBoxSlaveI2C library

This class describes the "slave" side of the pond 
 
MIT license
written by Berto 'd Sera
*/

#ifndef DistributedPlanterBoxSlaveI2C_h
#define DistributedPlanterBoxSlaveI2C_h

#include "Arduino.h"
#include <DistributedServiceI2CSlave.h>
#include <DistributedPlanterBoxSlave.h>


class DistributedPlanterBoxSlaveI2C : public virtual DistributedServiceI2CSlave {    
  public:
    DistributedPlanterBoxSlaveI2C(uint8_t);
};

#endif
