/* DistributedServiceI2CSlave library
 
This class describes the "slave" side of the pond  
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DistributedServiceI2CCore.h>
#include <DistributedServiceI2CSlave.h>
#include <WSWire.h>

// base for polimorphism
DistributedService *node;


// Callback wrappers
void slaveSendWrapper(void) { node->slaveSend(); }
void slaveGetWrapper(int howMany) { node->slaveGet(); }


DistributedServiceI2CSlave::DistributedServiceI2CSlave(uint8_t _id, uint8_t _payloadSize) :
  DistributedService( _id, _payloadSize ), 
  DistributedServiceI2CCore( _id, _payloadSize, false ) {  

  // register callbacks
  Wire.onReceive(slaveGetWrapper);    
  Wire.onRequest(slaveSendWrapper); 
}


void DistributedServiceI2CSlave::slaveSend(void) {
  Serial.println(F("Sending "));   
  servicePayload[0]=99;
  slavePrepareSend();  
  coreSend();   
}
  
void DistributedServiceI2CSlave::slaveGet(void) {
  coreGet();
  
  // check CRC before using the data, ignore if not valid
  // TODO set error LED on CRC error
  if (isValid()) {
    slaveImplementGet();   
  }  
}



