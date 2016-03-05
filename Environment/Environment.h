/* Environment library
  
A model of the flat, air, humidity, light, weather, heating, etc

MIT license
written by Berto 'd Sera
*/

#ifndef Environment_h
#define Environment_h

#include "Arduino.h"
#include <NetworkInterface.h>
#include <Daylight.h>
#include <Luxmetre.h>
#include <Hygrometre.h>
#include <Weather.h>

class Environment {
  private:
    NetworkInterface *net;
    String           longitude;
    String           latitude;
    Daylight         *sunshine; 
    Luxmetre         *luxmetre;   
    Hygrometre       *hygrometre;
    Weather          *weather;
    //moonphase
  public:
    Environment(NetworkInterface*&, String, String);
    bool   sunLight(void);
    bool   light(void);    
    time_t timeToSunset(void);
    time_t timeToDark(void);     
    
    double altitude(void);
    double temperature(void);    
    double pressure(void); 
    double pressureSeaLevel(void);    
    
    double infrared(void);
    double visibleLight(void); 
    double fullLight(void); 
    double lux(void); 
    
    double temperatureHygro(void);    
    double humidity(void); 
    double dewPoint(void);   
    double heatIndex(void);
};

#endif