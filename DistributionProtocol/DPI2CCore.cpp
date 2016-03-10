/* DPI2CCore library
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DistributionProtocol.h>
#include <DPI2CCore.h>
#include <WSWire.h>


DPI2CCore::DPI2CCore(uint8_t _id, uint8_t _payloadSize, bool _master) 
  : DistributionProtocol( _id, _payloadSize ) {  

  // join i2c bus with address
  if (_master) {
    Wire.begin();    
  } else {  
    Wire.begin(serviceId);
  }  
}


void DPI2CCore::coreSend(void) {
  Serial.println(F("Sending data "));    
  
  // copy the box map top the protocol buffer
  //memcpy ( box->mapAddress(), servicePayload, sizeOfPayload );  
  
  // compute crc to send
  servicePayload[sizeOfPayload] = CRC8(servicePayload, sizeOfPayload);
  
  // send it out
  Wire.write(servicePayload,sizeOfPayload+1);

  // report  
  inspect();
}


void DPI2CCore::coreGet(void) {
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
  
  // copy the protocol buffer to the box map (ignore on bad crc) 
  if (isValid()) { 
    //memcpy ( servicePayload, box->mapAddress(), sizeOfPayload );
  }    
}   
    