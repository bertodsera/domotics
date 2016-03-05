/* DistributedServiceI2CCore library
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DistributedService.h>
#include <DistributedServiceI2CCore.h>
#include <WSWire.h>


DistributedServiceI2CCore::DistributedServiceI2CCore(uint8_t _id, uint8_t _payloadSize, bool _master) 
  : DistributedService( _id, _payloadSize ) {  

  // join i2c bus with address
  if (_master) {
    Wire.begin(1);    
  } else {  
    Wire.begin(serviceId);
  }  
}


void DistributedServiceI2CCore::coreSend(void) {
  servicePayload[sizeOfPayload] = CRC8(servicePayload, sizeOfPayload);
  Wire.write(servicePayload,sizeOfPayload+1);  
  inspect();
}


void DistributedServiceI2CCore::coreGet(void) {
  uint8_t index   = 0;
  
  // Make sure we write on a blank
  erasePayload();

  while(Wire.available())    // slave may send less than requested
  { 
    if ( index <= sizeOfPayload ) {
      servicePayload[index] = Wire.read(); // receive a byte    
    }  
    else {
      // NOTE! This should never happen, it would mean the client is 
      // sending over more bytes than we requested 
      Wire.read(); // throw it away
      Serial.println(F("Throwing away data "));  
    }  
    index++;
  }
}   
    