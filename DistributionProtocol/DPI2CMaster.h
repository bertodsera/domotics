/* DPI2CMaster library
 
This class describes the "master" side of the pond 
 
MIT license
written by Berto 'd Sera
*/

#ifndef DPI2CMaster_h
#define DPI2CMaster_h

#include "Arduino.h"
#include <DPI2CCore.h>

class DPI2CMaster : public virtual DPI2CCore {   
  public:
    DPI2CMaster(uint8_t, uint8_t);
    
    // payload transport commands
    void masterSend(void);
    void masterGet(void);   
};

#endif


