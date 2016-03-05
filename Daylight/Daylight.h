/* Daylight library
  
A model of the light available during the current day

MIT license
written by Berto 'd Sera
*/

#ifndef Daylight_h
#define Daylight_h

#include "Arduino.h"
#include <Time.h>
#include <NetworkInterface.h>

class Daylight {
  private:
    time_t  date;
    bool    jstatus;
    time_t  sunrise; 
    time_t  sunset;  
    time_t  solar_noon;  
    word    day_length;    
    time_t  civil_twilight_begin;  
    time_t  civil_twilight_end;
    time_t  nautical_twilight_begin;
    time_t  nautical_twilight_end;
    time_t  astronomical_twilight_begin;
    time_t  astronomical_twilight_end; 
    void    inspect(void);    
  public:
    Daylight(void);
    bool   needsRefresh(void);    
    void   refresh(NetworkInterface*&, String, String);
    time_t timeToSunset(void);
    time_t timeToDark(void);  
    bool   sunLight(void);
    bool   light(void);        
};

#endif