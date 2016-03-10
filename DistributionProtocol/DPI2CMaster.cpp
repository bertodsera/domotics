/* DPI2CMaster library

This class describes the "master" side of the pond 
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DistributionProtocol.h>
#include <DPI2CCore.h>
#include <DPI2CMaster.h>
#include <WSWire.h>


DPI2CMaster::DPI2CMaster(uint8_t _id, uint8_t _payloadSize) : 
  DistributionProtocol( _id, _payloadSize ), 
  DPI2CCore( _id, _payloadSize, true ) {  }


void DPI2CMaster::masterSend(void) {
  Wire.beginTransmission(serviceId); // transmit to remote device
  
  coreSend();  
  
  Wire.endTransmission();    // stop transmitting
}


void DPI2CMaster::masterGet(void) {  
  // request payload + 1 byte crc
  uint8_t total = sizeOfPayload+1;
  Wire.requestFrom(serviceId, total);
  
  Serial.print(F("Requesting "));  
  Serial.println(serviceId);

  coreGet();
}   
    