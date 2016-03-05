/* DistributedServiceI2C library
 
This class describes the "master" side of the pond 
 
MIT license
written by Berto 'd Sera
*/

#ifndef DistributedServiceI2C_h
#define DistributedServiceI2C_h

#include "Arduino.h"
#include <DistributedServiceI2CCore.h>

class DistributedServiceI2C : public virtual DistributedServiceI2CCore {   
  public:
    DistributedServiceI2C(uint8_t, uint8_t);
    
    // payload transport commands
    void masterSend(void);
    void masterGet(void);   
};

#endif


