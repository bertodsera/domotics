#include <WSWire.h>
#include <GenericPin.h>
#include <AnalogPin.h>
#include <DigitalPin.h>
#include <PwmPin.h>
#include <DBox.h>
#include <DPlanterBox.h>
#include <DPlanterBoxSlave.h>
#include <DPlanterBoxMaster.h>
#include <PollingSensor.h>
#include <SoilHumiditySensor.h>

DBox *node;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting "));  
  node = new DPlanterBoxSlave();
  Serial.println(F("Started "));  
  node->update();  
  node->inspectBox(); 
};

void loop() {
  delay(2000);
  node->update();  
  node->inspectBox();  
};



