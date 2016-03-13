/* DPlanterBox library

This interface describes the basics of the planter box service (it is transport agnostic)
 
MIT license
written by Berto 'd Sera
*/

#include "Arduino.h"
#include <DBox.h>
#include <DPlanterBox.h>


DPlanterBox::DPlanterBox(void) : DBox() {
  for ( uint8_t a = 0; a < PLANTERBOXPAYLOAD; a++ ) {    
    map.serialValue[a] = 0;
  }  
}


void * DPlanterBox::mapAddress(void) {
 void *a = &map;
 return a; 
}  


void DPlanterBox::inspectBox(void) {
  Serial.println(F("Planter Box")); 
  Serial.println(F("===================================="));   
  Serial.print(F("Humidity: ")); 
  Serial.print(map.box[0].humidity);
  Serial.print(F("% | "));   
  Serial.print(map.box[1].humidity);  
  Serial.println(F("%"));
  
  Serial.print(F("Map: "));
  Serial.print((int)PLANTERBOXPAYLOAD);   
  Serial.print(F(" "));
  for ( uint8_t a = 0; a < PLANTERBOXPAYLOAD; a++ ) {  
    Serial.print(F("/"));  
    // convert byte to int to make it printable
    Serial.print((int)map.serialValue[a]);     
  }  
  Serial.println();  
  Serial.println(F("===================================="));  
}


uint8_t DPlanterBox::index(bool _side) {
  // true == right
  if (_side) { return PLANTER_R; }
  else { return PLANTER_L; }
}