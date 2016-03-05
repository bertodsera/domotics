/* DistributedServiceI2C library
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DistributedService.h>
#include <DistributedServiceI2CCore.h>
#include <DistributedServiceI2C.h>
#include <WSWire.h>


DistributedService *remotenode;


DistributedServiceI2C::DistributedServiceI2C(uint8_t _id, uint8_t _payloadSize) : 
  DistributedService( _id, _payloadSize ), 
  DistributedServiceI2CCore( _id, _payloadSize ) {  }


void DistributedServiceI2C::masterSend(void) {
  Wire.beginTransmission(serviceId); // transmit to remote device
  
  coreSend();  
  
  Wire.endTransmission();    // stop transmitting
}


void DistributedServiceI2C::masterGet(void) {  
  Wire.requestFrom(serviceId, sizeOfPayload);    // request 6 bytes from slave device #2

  coreGet();
}   
    