/* DistributedServiceI2CSlave library

This class describes the "slave" side of the pond 
 
MIT license
written by Berto 'd Sera
*/

#ifndef DistributedServiceI2CSlave_h
#define DistributedServiceI2CSlave_h

#include "Arduino.h"
#include <DistributedServiceI2CCore.h>


class DistributedServiceI2CSlave : public virtual DistributedServiceI2CCore {   
  public:
    DistributedServiceI2CSlave(uint8_t, uint8_t);
    
    // payload transport commands
    void slaveSend(void);
    void slaveGet(void);  
};

#endif

