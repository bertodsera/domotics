/* DistributedPlanterBox library

This interface describes the basics of the planter box service (it is transport agnostic)
versions currently planned
  - I2C
  - Bluetooth
 
MIT license
written by Berto 'd Sera
*/

#ifndef DistributedPlanterBox_h
#define DistributedPlanterBox_h

#include "Arduino.h"
#define PLANTERBOXPAYLOAD 10

#define PLANTER_R 0
#define PLANTER_L 1

#define CONNECTED_PIN 0b00000001 
#define BUZZER_PIN    0b00000010 
#define REFRESH_PIN   0b00001000 
#define OK_PIN        0b00010000 
#define WATER_PIN     0b00100000 
#define ERROR_PIN     0b01000000 

/* PAYLOAD for a Planter box 10 bytes
 =====================================
 serialized image of a side of the box
   analog  sensors = 2*4 bytes;
   digital I/O     = 2*1 byte;
  */
typedef struct PlanterMap {
  // 4 bytes
  float humidity;
  // 1 byte
  byte  pins;
};

// Serialized information
typedef union BoxMap {
  PlanterMap box[2];
  byte       serialValue[PLANTERBOXPAYLOAD];
};


class DistributedPlanterBox {   
  protected:
    BoxMap map;
    // function used to univocally decode the right/left boolean selector
    uint8_t index(bool);    
    
  public:
    DistributedPlanterBox();
    
    void inspectPlanterBox(void);  
};

#endif


