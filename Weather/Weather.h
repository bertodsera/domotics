/* Weather library
  
A thermometre/barometre sensor

MIT license
written by Berto 'd Sera
*/

#ifndef Weather_h
#define Weather_h

#define ALTITUDE 35.0
#include "Arduino.h"
#include <Time.h>
#include <SFE_BMP180.h>

class Weather {
  private:
    SFE_BMP180 *sensor;
    time_t     lastReading;
    time_t     validity;
    double     temperatureValue;
    double     pressureValue; 
    double     pressureSeaLevelValue;      
    void       refresh();
  public:
    Weather(time_t);
    double altitude();
    double temperature();    
    double pressure(); 
    double pressureSeaLevel();     
};

#endif