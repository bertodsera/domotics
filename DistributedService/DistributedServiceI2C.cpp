/* DistributedServiceI2C library

This class describes the "master" side of the pond 
 
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
  DistributedServiceI2CCore( _id, _payloadSize, true ) {  }


void DistributedServiceI2C::masterSend(void) {
  Wire.beginTransmission(serviceId); // transmit to remote device
  
  coreSend();  
  
  Wire.endTransmission();    // stop transmitting
}


void DistributedServiceI2C::masterGet(void) {  
  // request payload + 1 byte crc
  uint8_t total = sizeOfPayload+1;
  Wire.requestFrom(serviceId, total);
  
  Serial.print(F("Requesting "));  
  Serial.println(serviceId);

  coreGet();
}   
    