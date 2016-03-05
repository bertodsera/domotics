/* Hygrometre library
  
A thermometre/hygrometre sensor

MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <Time.h>
#include <Logger.h>
#include <DHT.h>
#include <Hygrometre.h>

Hygrometre::Hygrometre(time_t _validity) {  
  const char *msgSensorFound = "Hygrometre: sensor found";  
  
  lastReading      = 0;
  validity         = _validity;
  temperatureValue = 0.0;
  humidityValue    = 0.0;
  dewPointValue    = 0.0;
  heatIndexValue   = 0.0;

  sensor = new DHT(19, DHT22);
  sensor->begin();
  
  log(msgSensorFound);
}


void Hygrometre::refresh() {
  humidityValue    = sensor->readHumidity();
  temperatureValue = sensor->readTemperature();
  dewPointValue    = temperatureValue - (100 - humidityValue)/5.0;
  heatIndexValue   = sensor->computeHeatIndex(temperatureValue, humidityValue, false);
  
  lastReading = now();
}

double Hygrometre::temperature() {
  if ( (now() - lastReading) > validity ) {
    refresh();
  }  
  return temperatureValue;    
}

double Hygrometre::humidity() {
  if ( (now() - lastReading) > validity ) {
    refresh();
  }  
  return humidityValue;      
} 

double Hygrometre::dewPoint() {
  if ( (now() - lastReading) > validity ) {
    refresh();
  }  
  return dewPointValue;      
}   

double Hygrometre::heatIndex() {
  if ( (now() - lastReading) > validity ) {
    refresh();
  }  
  return heatIndexValue;      
}