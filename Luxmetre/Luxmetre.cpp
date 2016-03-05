/* Luxmetre library
  
A luxmetre sensor

MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <Time.h>
#include <Logger.h>
#include <TSL2561.h>
#include <Luxmetre.h>
    
Luxmetre::Luxmetre(time_t _validity) {
  const char *msgSensorFound    = "Luxmetre::Luxmetre Found TSL2561 sensor";
  const char *msgSensorNotFound = "Luxmetre::Luxmetre No TSL2561 sensor?";  
  
  lastReading           = 0;
  validity              = _validity;
  infraredLightValue    = 0;
  visibleLightValue     = 0;
  luxValue              = 0;
  
  // Set I2C address
  sensor = (new TSL2561(TSL2561_ADDR_FLOAT));
  
  if (sensor->begin()) {
    log(msgSensorFound);
  } else {
    log(msgSensorNotFound);
    while (1);
  }
    
  // You can change the gain on the fly, to adapt to brighter/dimmer light situations
  //sensor->setGain(TSL2561_GAIN_0X);         // set no gain (for bright situtations)
  sensor->setGain(TSL2561_GAIN_16X);      // set 16x gain (for dim situations)
  
  // Changing the integration time gives you a longer time over which to sense light
  // longer timelines are slower, but are good in very low light situtations!
  //sensor->setTiming(TSL2561_INTEGRATIONTIME_13MS);  // shortest integration time (bright light)
  //sensor->setTiming(TSL2561_INTEGRATIONTIME_101MS);  // medium integration time (medium light)
  sensor->setTiming(TSL2561_INTEGRATIONTIME_402MS);  // longest integration time (dim light)
}


void Luxmetre::refresh() {
  uint32_t lum = sensor->getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  
  infraredLightValue = ir / 16.0;
  visibleLightValue  = (full - ir) / 16.0;
  luxValue           = sensor->calculateLux(full, ir);
  lastReading        = now();
}
    
    
double Luxmetre::infrared() {
  if ( (now() - lastReading) > validity ) {
    refresh();
  }  
  return infraredLightValue;
}


double Luxmetre::visible() {
  if ( (now() - lastReading) > validity ) {
    refresh();
  }  
  return visibleLightValue;  
} 


double Luxmetre::full() {
  if ( (now() - lastReading) > validity ) {
    refresh();
  }  
  return (infraredLightValue + visibleLightValue);  
} 


double Luxmetre::lux() {
  if ( (now() - lastReading) > validity ) {
    refresh();
  }  
  return luxValue; 
}     

