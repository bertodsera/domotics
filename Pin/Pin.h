/* Pin library

MIT license
written by Berto 'd Sera
*/
#ifndef Pin_h
#define Pin_h

#include "Arduino.h"

#undef int
#undef float
#undef abs
#undef round

#ifndef GenericPin_h
#define GenericPin_h
#include <GenericPin.h>
#endif

#ifndef DigitalPin_h
#define DigitalPin_h
#include <DigitalPin.h>
#endif

#ifndef PwmPin_h
#define PwmPin_h
#include <PwmPin.h>
#endif

#ifndef AnalogPin_h
#define AnalogPin_h
#include <AnalogPin.h>
#endif

#endif

