/* Weather library
  
A thermometre/barometre sensor

MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <Time.h>
#include <Logger.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include <Weather.h>

Weather::Weather(time_t _validity) {
  lastReading           = 0;
  validity              = _validity;
  temperatureValue      = 0;
  pressureValue         = 0;
  pressureSeaLevelValue = 0;
  
    // Set I2C address
  sensor = (new SFE_BMP180());
  
  if (sensor->begin())
    log("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.
    log("BMP180 init fail! Check connections!");
    while(1); // Pause forever.
  }    
}


double Weather::altitude(void) {
  return ALTITUDE;
}


double Weather::temperature(void) {
  if ( (now() - lastReading) > validity ) {
    refresh();
  }
  return temperatureValue;
}


double Weather::pressure(void) {
  if ( (now() - lastReading) > validity ) {
    refresh();
  }  
  return pressureValue;  
}


double Weather::pressureSeaLevel(void) {
  if ( (now() - lastReading) > validity ) {
    refresh();
  }  
  return pressureSeaLevelValue;
}  


void Weather::refresh() {
  char status;
  double p0,a;

  status = sensor->startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.
    status = sensor->getTemperature(temperatureValue);
    
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.
      status = sensor->startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.
        status = sensor->getPressure(pressureValue,temperatureValue);
    
        if (status != 0)
        {
          // The pressure sensor returns abolute pressure, which varies with altitude.
          // To remove the effects of altitude, use the sealevel function and your current altitude.
          // This number is commonly used in weather reports.
          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
          // Result: p0 = sea-level compensated pressure in mb
          pressureSeaLevelValue = sensor->sealevel(pressureValue,ALTITUDE); // we're at ALTITUDE meters 

          // timestamp the values
          lastReading = now();
        }
        else log("Weather::refresh error retrieving pressure measurement");
      }
      else log("Weather::refresh error starting pressure measurement");
    }
    else log("Weather::refresh error retrieving temperature measurement");
  }
  else log("Weather::refresh error starting temperature measurement");  
}