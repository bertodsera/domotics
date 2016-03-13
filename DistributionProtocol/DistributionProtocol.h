/* DistributionProtocol library

  Interface for distributed network. The actual network transport can use either I2C or Bluetooth, and it is 
  specified in the derived classes.
 
MIT license
written by Berto 'd Sera
*/

#ifndef DistributionProtocol_h
#define DistributionProtocol_h

#include "Arduino.h"
#include <DBox.h>

class DistributionProtocol {
  protected: 
    // Pointer to the wrapped hardware
    DBox *box;     
    
    /* Values used by slave callback functions
      
       Resident Payload    
       ----------------
          This is just an array of bytes. It knows nothing of the 
          objects that will point to it, to decode it */
    byte *servicePayload;   
  
    // Load payload from box into protocol memory
    void readFromBox(void);  
    
    // upload payload to box from protocol memory
    void writeToBox(void);       
    
    /* Payload size in bytes (gets set on init)
       this is how many bytes belong to a single node
     */ 
    uint8_t sizeOfPayload;    
    
    // Service identity on the distribution network (remote node id)
    uint8_t serviceId;   
    
    // utils
    void erasePayload(void);
    byte CRC8(const byte*, byte);
    
  public:
    DistributionProtocol(uint8_t, uint8_t);
    
    // payload transport commands
    virtual void masterSend(void) {};
    virtual void masterGet(void) {};   
    virtual void slaveSend(void) {};
    virtual void slaveGet(void) {}; 
    
    // actual actions triggered by the callbacks
    virtual void slaveImplementGet(void) {};    
    virtual void slavePrepareSend(void) {};       
        
    // actual services implemented at this level
    void inspect(void);   // print out servicePayload  
    bool isValid(void);   // check crc      
};


#endif


