/* DistributedServiceI2CCore library
 
This class contains all I2C common parts shared by master and slave
 
MIT license
written by Berto 'd Sera
*/

#ifndef DistributedServiceI2CCore_h
#define DistributedServiceI2CCore_h

#include "Arduino.h"
#include <DistributedService.h>

class DistributedServiceI2CCore : public virtual DistributedService {   
  public:
    DistributedServiceI2CCore(uint8_t, uint8_t, bool);
    
    // payload transport core commands
    void coreSend(void);
    void coreGet(void);   
};

#endif


