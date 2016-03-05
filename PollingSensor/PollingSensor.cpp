/* PollingSensor library

MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <AnalogPin.h>
#include <DigitalPin.h>
#include <PollingSensor.h>

PollingSensor::PollingSensor(String name, const uint8_t& _analogPin, int _digitalPin, int _repeatReads, int _topValue, int _bottomValue ) 
    : AnalogPin(_analogPin) {
      
    setRead();  
      
    // store the sensor label, for reporting  
    label = name;  
      
    // create the driver pin and keep it switched off
    //   aka, no current through unless we are reading the sensor  
    driver = (new DigitalPin(_digitalPin));  
    driver->setWrite();
    driver->writeLow();
    
    // set number of reads to reach a stable value
    repeatReads = _repeatReads;
    
    // set the value bracket
    topValue = _topValue;
    bottomValue = _bottomValue;
    
    // compute the raw->percentage conversion factor
    conversionFactor = 100.0 / ( topValue - bottomValue );
    
    // set the polling service memory
    lastLevel = 0.0;
}


void PollingSensor::poll(void) {
  // switch the sensor on and read it, then switch it back off 
  driver->writeHigh(); 
  float sensor = stableValue(repeatReads);
  driver->writeLow();

  // Check that we are within the boundaries
  if ( sensor > topValue ) {
    sensor = topValue;
    Serial.print(F(" Sensor "));
    Serial.print(label);   
    Serial.println(F(" out of boundaries ")); 
  }
  if ( sensor < bottomValue )  {
    sensor = bottomValue;
    Serial.print(F(" Sensor "));
    Serial.print(label);   
    Serial.println(F(" out of boundaries ")); 
  }
  
  // compute the value
  lastLevel  = ((sensor - bottomValue) * conversionFactor);
}


float PollingSensor::level(bool _update) {
  if (_update) { 
    poll(); 
    
    // Log poll
    Serial.print(F(" Polling "));
    Serial.print(label);   
    Serial.print(F(" level measured: "));    
    Serial.println(lastLevel);        
  }

  return lastLevel;
}

