/* Logger library

MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <../Time/Time.h>
#include <../Logger/Logger.h>


String formatDigits(int digits) {
  String st = "";
  
  if(digits < 10)
    st = "0";

  return (st + String(digits));
}


String dayTime(void) {
  return ( formatDigits(day()) + "/" + 
           formatDigits(month()) + "/" + 
           formatDigits(year()) + " " + 
           formatDigits(hour()) + ":" + 
           formatDigits(minute()) + ":" + 
           formatDigits(second()) );
}  



String dayTime(time_t _date) {
  return ( formatDigits(day(_date)) + "/" + 
           formatDigits(month(_date)) + "/" + 
           formatDigits(year(_date)) + " " + 
           formatDigits(hour(_date)) + ":" + 
           formatDigits(minute(_date)) + ":" + 
           formatDigits(second(_date)) );
}  


String dayDate(time_t _date) {
  return ( formatDigits(day(_date)) + "/" + 
           formatDigits(month(_date)) + "/" + 
           formatDigits(year(_date)) );
}  


void log(String _entry) {
  String formatted_entry;
  
  // Add time if we have it
  if (timeStatus()==timeSet) {
    formatted_entry += dayTime();
    formatted_entry += ' ';  
  }
  formatted_entry += _entry;  
  
  Serial.println(formatted_entry);
}


String formatFloat(double _value, int _intdigits, int _decdigits) {
  const int tmplen = _intdigits + _decdigits + 2;
  char tmp[tmplen];  
  dtostrf(_value, (tmplen-1), _decdigits, tmp);  
  
  return tmp;
}