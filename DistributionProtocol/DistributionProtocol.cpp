/* DistributionProtocol library
 
  Interface for distributed function. The actual network transport can use either I2C or Bluetooth, and it is 
  specified in the derived classes.
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DistributionProtocol.h>


DistributionProtocol::DistributionProtocol(uint8_t _id, uint8_t _payloadSize) {
  serviceId      = _id;
  sizeOfPayload  = _payloadSize;
  servicePayload = new byte[sizeOfPayload+1];
  erasePayload();
}


//CRC-8 - based on the CRC8 formulas by Dallas/Maxim
//code released under the therms of the GNU GPL 3.0 license
// http://www.leonardomiliani.com/en/2013/un-semplice-crc8-per-arduino/
byte DistributionProtocol::CRC8(const byte *data, byte len) {
  byte crc = 0x00;
  
  while (len--) {
    byte extract = *data++;
    for (byte tempI = 8; tempI; tempI--) {
      byte sum = (crc ^ extract) & 0x01;
      crc >>= 1;
      if (sum) {
        crc ^= 0x8C;
      }
      extract >>= 1;
    }
  }
  return crc;
}


void DistributionProtocol::erasePayload(void) {
  for ( uint8_t a = 0; a < sizeOfPayload; a++ ) {  
    servicePayload[a] = 0;   
  }
  // put broken crc
  servicePayload[sizeOfPayload] = 255;
}


void DistributionProtocol::inspect(void) {
  Serial.print(F("Payload: "));
  Serial.print((int)sizeOfPayload);   
  Serial.print(F(" "));
  
  for ( uint8_t a = 0; a < sizeOfPayload; a++ ) {  
    Serial.print(F("/"));  
    // convert byte to int to make it printable
    Serial.print((int)servicePayload[a]);     
  }
  
  Serial.print(F("   CRC: "));
  Serial.print((int)servicePayload[sizeOfPayload]);   
  Serial.print(F("/"));
  Serial.print((int)CRC8(servicePayload, sizeOfPayload));   
  Serial.println();   
}    


bool DistributionProtocol::isValid(void) {
  return (servicePayload[sizeOfPayload] == CRC8(servicePayload, sizeOfPayload));
}