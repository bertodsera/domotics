/* DPI2CSlave library
 
This class describes the "slave" side of the pond  
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DistributionProtocol.h>
#include <DPI2CCore.h>
#include <DPI2CSlave.h>
#include <WSWire.h>

// Pointer to the instance for this protocol
// it will implement the DistributionProtocol interface
DPI2CSlave *node;


// Callback wrapper functions
void slaveSendWrapper(void) { 
  if (node) {
    node->slaveSend();
  }
  else { Serial.println(F("Node is NULL, skipping send")); }
}

void slaveGetWrapper(int howMany) { 
  Serial.println((uint16_t)node,HEX);
  if (node) {
    Serial.println(F("Getting"));
    node->slaveSend();
  }
  else { Serial.println(F("Skip get")); }
}



DPI2CSlave::DPI2CSlave(uint8_t _id, uint8_t _payloadSize) :
  DistributionProtocol( _id, _payloadSize ), 
  DPI2CCore( _id, _payloadSize, false ) {  

  // register callbacks
  Wire.onReceive(slaveGetWrapper);    
  Wire.onRequest(slaveSendWrapper);     
}


void DPI2CSlave::slaveSend(void) {
  Serial.println(F("--test--"));    
  slavePrepareSend();  
  coreSend();  
}
  
void DPI2CSlave::slaveGet(void) {
  // check CRC before using the data, ignore if not valid
  // TODO set error LED on CRC error
  if (isValid()) {
   // slaveImplementGet();   
  }  
}


void DPI2CSlave::test(void) {
  Serial.println(F("--test--"));  
}


