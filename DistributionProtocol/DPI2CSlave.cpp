/* DPI2CSlave library
 
This class describes the "slave" side of the pond  
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DPI2CCore.h>
#include <DPI2CSlave.h>
#include <WSWire.h>

// base for polimorphism
DistributedProtocol *node;


// Callback wrappers
void slaveSendWrapper(void) { node->slaveSend(); }
void slaveGetWrapper(int howMany) { node->slaveGet(); }


DPI2CSlave::DPI2CSlave(uint8_t _id, uint8_t _payloadSize) :
  DistributedProtocol( _id, _payloadSize ), 
  DPI2CCore( _id, _payloadSize, false ) {  

  // register callbacks
  Wire.onReceive(slaveGetWrapper);    
  Wire.onRequest(slaveSendWrapper); 
}


void DPI2CSlave::slaveSend(void) {
  Serial.println(F("Sending "));   
  servicePayload[0]=99;

  coreSend();   
}
  
void DPI2CSlave::slaveGet(void) {
  coreGet(); 
}



