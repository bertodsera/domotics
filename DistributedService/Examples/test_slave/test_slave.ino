

#include <WSWire.h>
#include <GenericPin.h>
#include <AnalogPin.h>
#include <DigitalPin.h>
#include <PwmPin.h>
#include <PollingSensor.h>
#include <SoilHumiditySensor.h>

#include <DBox.h>
#include <DPlanterBox.h>
#include <DPlanterBoxMaster.h>
#include <DPlanterBoxSlave.h>

#include <DistributionProtocol.h>
#include <DPI2CCore.h>
#include <DPI2CMaster.h>
#include <DPI2CSlave.h>

#include <DPlanterBoxSlaveI2C.h>

void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting ")); 
  
  node = new DPlanterBoxSlaveI2C(2);

  Serial.println(F("Ready"));   
};

void loop() {
  delay(200);
};





