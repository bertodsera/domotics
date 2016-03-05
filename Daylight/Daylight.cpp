/* Daylight library
  
A model of the light available during the current day

MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <Time.h>
#include <Logger.h>
#include <NetworkInterface.h>
#include <ArduinoJson.h>
#include <Daylight.h>

time_t castToTime(String value) {
  static tmElements_t tm; 
  
  // Typical value format: "2016-02-13T07:18:48+00:00"  
  tm.Year   = (atoi(value.substring(0,4).c_str()) - 1970); 
  tm.Month  = atoi(value.substring(5,7).c_str()); 
  tm.Day    = atoi(value.substring(8,10).c_str());
  tm.Hour   = atoi(value.substring(11,13).c_str());
  tm.Minute = atoi(value.substring(14,16).c_str());
  tm.Second = atoi(value.substring(17,19).c_str()); 

  return makeTime(tm);
}




Daylight::Daylight(void) {
  date                        = 0;
  jstatus                     = false;
  sunrise                     = 0; 
  sunset                      = 0;  
  solar_noon                  = 0;  
  day_length                  = 0;    
  civil_twilight_begin        = 0;  
  civil_twilight_end          = 0;
  nautical_twilight_begin     = 0;
  nautical_twilight_end       = 0;
  astronomical_twilight_begin = 0;
  astronomical_twilight_end   = 0; 
}



void Daylight::refresh(NetworkInterface*& _eth0, String _lat, String _lng) { 
  const char *refreshMsgStringTooLong = "Daylight::refresh string too long: ";
  const char *refreshMsgParseFailed   = "Daylight::refresh parseObject() failed";
  const char *msgChars                = "chars";  
  StaticJsonBuffer<500> jsonBuffer;
  char json[500] = { 0 };
  
  // retrieve the value from api.sunrise-sunset.org
  String answer = _eth0->getSunriseSunset(_lat, _lng);
  
  // make sure we are not too long
  if (answer.length()+1 > 498) {
    //log("Daylight::refresh site answered " + String(answer.length()+1));    
    log(refreshMsgStringTooLong + String(answer.length()+1) + msgChars);  
    return;
  }
  
  answer.toCharArray(json,(answer.length()+1));
  JsonObject& root = jsonBuffer.parseObject(json);  
  
  // Test if parsing succeeds.
  if (!root.success()) {
    log(refreshMsgParseFailed);
    return;
  }

  // update data is the answer is valid
  const char* _jstatus = root["status"];  
  if ( strcmp( _jstatus, "OK") == 0 ) {
    jstatus = true;

    // update data time tag
    date = now();
  
    // get values as strings
    const char* _sunrise                     = root["results"]["sunrise"]; 
    const char* _sunset                      = root["results"]["sunset"];  
    const char* _solar_noon                  = root["results"]["solar_noon"];  
    const char* _day_length                  = root["results"]["day_length"];    
    const char* _civil_twilight_begin        = root["results"]["civil_twilight_begin"];  
    const char* _civil_twilight_end          = root["results"]["civil_twilight_end"];
    const char* _nautical_twilight_begin     = root["results"]["nautical_twilight_begin"];
    const char* _nautical_twilight_end       = root["results"]["nautical_twilight_end"];  
    const char* _astronomical_twilight_begin = root["results"]["astronomical_twilight_begin"];
    const char* _astronomical_twilight_end   = root["results"]["astronomical_twilight_end"];   
  
    // record numeric values castToTime(String value)
    sunrise                     = castToTime(_sunrise);
    sunset                      = castToTime(_sunset); 
    solar_noon                  = castToTime(_solar_noon); 
    day_length                  = atoi(_day_length);   
    civil_twilight_begin        = castToTime(_civil_twilight_begin); 
    civil_twilight_end          = castToTime(_civil_twilight_end);
    nautical_twilight_begin     = castToTime(_nautical_twilight_begin);
    nautical_twilight_end       = castToTime(_nautical_twilight_end);
    astronomical_twilight_begin = castToTime(_astronomical_twilight_begin);
    astronomical_twilight_end   = castToTime(_astronomical_twilight_end);
    
    // log result
    inspect();
  }
} 


void Daylight::inspect(void) {
  const char *arrow                     = " --> ";
  const char *validData                 = "Valid data: ";
  const char *dateDescribed             = "Date described: ";
  const char *sunriseStr                = "sunrise: ";
  const char *sunsetStr                 = "sunset: ";
  const char *solarNoon                 = "solar_noon: ";
  const char *dayLength                 = "day_length: ";
  const char *civilTwilightBegin        = "civil_twilight_begin: ";
  const char *civilTwilightEnd          = "civil_twilight_end: ";
  const char *nauticalTwilightBegin     = "nautical_twilight_begin: ";
  const char *nauticalTwilightEnd       = "nautical_twilight_end: ";
  const char *astronomicalTwilightBegin = "astronomical_twilight_begin: ";
  const char *astronomicalTwilightEnd   = "astronomical_twilight_end: ";

  log(validData + String(jstatus));
  log(dateDescribed + String(date) + arrow + dayDate(date));
  log(sunriseStr + String(sunrise) + arrow + dayTime(sunrise));
  log(sunsetStr + String(sunset) + arrow + dayTime(sunset));
  log(solarNoon + String(solar_noon) + arrow + dayTime(solar_noon));  
  log(dayLength + String(day_length));
  log(civilTwilightBegin + String(civil_twilight_begin) + arrow + dayTime(civil_twilight_begin));
  log(civilTwilightEnd + String (civil_twilight_end) + arrow + dayTime(civil_twilight_end));
  log(nauticalTwilightBegin + String(nautical_twilight_begin) + arrow + dayTime(nautical_twilight_begin));
  log(nauticalTwilightEnd + String(nautical_twilight_end) + arrow + dayTime(nautical_twilight_end));
  log(astronomicalTwilightBegin + String(astronomical_twilight_begin) + arrow + dayTime(astronomical_twilight_begin));
  log(astronomicalTwilightEnd + String(astronomical_twilight_end) + arrow + dayTime(astronomical_twilight_end));    
}


bool Daylight::needsRefresh(void) {
  return (day(date) != day(now()));
}


time_t Daylight::timeToSunset(void) {
  if (now() >= sunset) 
  { return 0; }
  else 
  { return (sunset-now()); };
}


time_t Daylight::timeToDark(void) {
  if (now() >= civil_twilight_end) 
  { return 0; }
  else 
  { return (civil_twilight_end-now()); };
}


bool Daylight::sunLight(void) {
  return ( (now() <= sunset) && (now() >= sunrise) );
}


bool Daylight::light(void) {
  return ( (now() <= civil_twilight_end) && (now() >= civil_twilight_begin) ); 
}    
