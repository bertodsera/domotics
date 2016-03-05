/* Hygrometre library
  
A thermometre/hygrometre sensor

MIT license
written by Berto 'd Sera
*/

#ifndef Hygrometre_h
#define Hygrometre_h

#include "Arduino.h"
#include <Time.h>
#include <DHT.h>

class Hygrometre {
  private:
    DHT    *sensor; 
    time_t lastReading;
    time_t validity;
    double temperatureValue;
    double humidityValue; 
    double dewPointValue;   
    double heatIndexValue;
    void   refresh();
  public:
    Hygrometre(time_t);
    double temperature(void);    
    double humidity(void); 
    double dewPoint(void);
    double heatIndex(void);
};

#endif