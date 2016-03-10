/* DBox library

A "Distributed box" is de-centralized unit, performing a set of services. Usually it will be another Arduino, that
  is in charge of something. A DBox has two halves:
  - master (the "image" of the remote box, as maintained inside the master)
  - slave (the actual de-centralized controller)
  
A DBox knows nothing of how master and server talk to each other. It only describes the hardware of the slave, and it 
implements the set of commands the master uses to perform remote operations. How the halves keep in sync is dealt with 
by the DistributedService family of classes.

This interface describes the basics of the "Dbox" service, 
  it simply implements the mechanism by which the wrapping protocol class can read/write to a box's memory map
 
MIT license
written by Berto 'd Sera
*/

#ifndef DBox_h
#define DBox_h

#include "Arduino.h"

class DBox {    
  public:
    DBox() {};

    virtual void * mapAddress(void) {};    
    virtual void inspectBox(void) {};  
    virtual void update(void) {}; 
};

#endif


