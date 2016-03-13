/* DPI2CSlave library

This class describes the "slave" side of the pond 
 
MIT license
written by Berto 'd Sera
*/

#ifndef DPI2CSlave_h
#define DPI2CSlave_h

#include "Arduino.h"
#include <DPI2CCore.h>


// Callback wrapper functions (forward declaration)
void slaveSendWrapper(void);
void slaveGetWrapper(int);


class DPI2CSlave : public virtual DPI2CCore {   
  public:
    DPI2CSlave(uint8_t, uint8_t);     
        
    // payload transport commands
    void slaveSend(void);
    void slaveGet(void);  
    
    // cycle for the box object
    void boxUpdate(void);
};

// There shall be an instance for this protocol
// it will implement this interface
extern DPI2CSlave *node;



#endif

