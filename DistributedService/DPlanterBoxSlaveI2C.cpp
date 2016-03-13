/* DPlanterBoxSlaveI2C library

This class implements the "slave" side of the planter service, on an I2C network 
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <WSWire.h>
#include <DistributionProtocol.h>
#include <DPI2CCore.h>
#include <DPI2CSlave.h>
#include <DPlanterBox.h>
#include <DPlanterBoxSlave.h>
#include <DPlanterBoxSlaveI2C.h>


DPlanterBoxSlaveI2C::DPlanterBoxSlaveI2C(uint8_t _id) :
  DistributionProtocol::DistributionProtocol( _id, PLANTERBOXPAYLOAD ), 
  DPI2CCore::DPI2CCore( _id, PLANTERBOXPAYLOAD, false ), 
  DPI2CSlave::DPI2CSlave(_id, PLANTERBOXPAYLOAD) {
  
  box = new DPlanterBoxSlave();  
  box->update();  
  
  box->inspectBox(); 
  readFromBox();
}


void DPlanterBoxSlaveI2C::slaveImplementGet(void) {
  
}    
    
void DPlanterBoxSlaveI2C::slavePrepareSend(void) {
  box->update(); 
}  






