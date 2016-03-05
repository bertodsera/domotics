/* Environment library
  
A model of the flat, air, humidity, light, weather, heating, etc

MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <Logger.h>
#include <Daylight.h>
#include <Luxmetre.h>
#include <Weather.h>
#include <Environment.h>

Environment::Environment(NetworkInterface*& _net, String _lat, String _lng) {
  net       = _net;
  longitude = _lng;
  latitude  = _lat;
  
  sunshine  = (new Daylight());
  sunshine->refresh(net, latitude, longitude); 
  delay(1000);
  
  luxmetre   = (new Luxmetre(60));
  delay(2000);
  
//  weather    = (new Weather(60));
//  delay(2000);  
  
  hygrometre = (new Hygrometre(60));
  delay(2000);  
}

time_t Environment::timeToSunset(void) {
  if (sunshine->needsRefresh()) {
    sunshine->refresh(net, latitude, longitude);
  }
  
  return sunshine->timeToSunset();
}


time_t Environment::timeToDark(void) {
  if (sunshine->needsRefresh()) {
    sunshine->refresh(net, latitude, longitude);
  }
  
  return sunshine->timeToDark();
}   


bool Environment::sunLight(void) {
  if (sunshine->needsRefresh()) {
    sunshine->refresh(net, latitude, longitude);
  }
  return sunshine->sunLight();
}

bool Environment::light(void)  {
  if (sunshine->needsRefresh()) {
    sunshine->refresh(net, latitude, longitude);
  }
  return sunshine->light();
} 



double Environment::altitude(void) {
  return weather->altitude();  
}

double Environment::temperature(void) {
  return weather->temperature();  
}

double Environment::pressure(void) {
  return weather->pressure();  
}


double Environment::pressureSeaLevel(void) {
  return weather->pressureSeaLevel();  
}
 
 
 
double Environment::infrared(void) {
  return luxmetre->infrared();
}

double Environment::visibleLight(void) {
  return luxmetre->visible();
}

double Environment::fullLight(void) {
  return luxmetre->full();
}

double Environment::lux(void) {
  return luxmetre->lux();
}



double Environment::temperatureHygro() {
  return hygrometre->temperature();
}

double Environment::humidity() {
  return hygrometre->humidity();
}

double Environment::dewPoint() {
  return hygrometre->dewPoint();
}


double Environment::heatIndex(void) {
  return hygrometre->heatIndex();
}