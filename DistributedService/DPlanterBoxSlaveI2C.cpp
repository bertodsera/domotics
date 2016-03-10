/* DistributedPlanterBoxSlaveI2C library

This class implements the "slave" side of the planter service, on an I2C network 
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DistributedService.h>
#include <DistributedServiceI2CCore.h>
#include <DistributedServiceI2CSlave.h>
#include <DistributedPlanterBox.h>
#include <DistributedPlanterBoxSlave.h>
#include <DistributedPlanterBoxSlaveI2C.h>

DistributedPlanterBoxSlaveI2C::DistributedPlanterBoxSlaveI2C(uint8_t _id) :
  DistributedService( _id, PLANTERBOXPAYLOAD ), 
  DistributedServiceI2CCore( _id, PLANTERBOXPAYLOAD, false ), 
  DistributedServiceI2CSlave::DistributedServiceI2CSlave(_id, PLANTERBOXPAYLOAD) {
  
  box = new DistributedPlanterBoxSlave();  
  box->update();  
  
  box->inspectBox();
}

