/* DPI2CCore library
 
This class contains all I2C common parts shared by master and slave
 
MIT license
written by Berto 'd Sera
*/

#ifndef DPI2CCore_h
#define DPI2CCore_h

#include "Arduino.h"
#include <DistributionProtocol.h>

class DPI2CCore : public virtual DistributionProtocol {   
  public:
    DPI2CCore(uint8_t, uint8_t, bool);
    
    // payload transport core commands
    void coreSend(void);
    void coreGet(void);   
};

#endif


