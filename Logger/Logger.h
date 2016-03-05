/* Logger library



MIT license
written by Berto 'd Sera
*/

#ifndef Logger_h
#define Logger_h

#include "Arduino.h"
#include <Time.h>

extern "C++" {
String formatDigits(int);  
String dayTime(void);
String dayTime(time_t);
String dayDate(time_t);
String formatFloat(double, int, int);
void   log(String);
}

#endif