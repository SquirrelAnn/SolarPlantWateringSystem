#include "waterpumpctrl.h"
#include <Arduino.h>

using namespace WaterPumpCtrl;

String waterPumpCtrl::epaperMsg(float sensorValue, int sensorNumber, int pumpNumber) {
  Serial.print("Soil moisture sensor ");
  Serial.print(sensorNumber);
  Serial.print(" value: ");
  Serial.print(sensorValue);
  Serial.println(" V"); // print voltage

  // 1.3V and lower --> super wet soil --> no watering
  // 2.3V and higher --> super dry soil --> watering
  // 2.75 or higher --> probably sensor is not in soil but in the air, don't water
  String pumpNo = "Pump";
  if (sensorValue >= 1.95 && sensorValue <= 2.6){ // adjusted range when to water according to testing phase
    String waterMsg = " 20s Watering.";
    String returnMsg = pumpNo + (pumpNumber - 1) + ":" + sensorValue + waterMsg;
    return returnMsg;
  } else {
    String waterMsg = " No watering.";
    String returnMsg = pumpNo + (pumpNumber - 1) + ":" + sensorValue + waterMsg;
    return returnMsg;
  }
}

bool waterPumpCtrl::water(float sensorValue, int sensorNumber, int pumpNumber){
  if (sensorValue >= 1.95 && sensorValue <= 2.6){ // adjusted range when to water according to testing phase
    digitalWrite(pumpNumber, LOW); // turn on pump
    delay(20000); // 20 seconds of watering (30s ~ 1Liter of water)
    digitalWrite(pumpNumber, HIGH); // turn off pump
    return true;
  } else {
    return false;
  }
}

float waterPumpCtrl::calcSoilHumid(int sensorPin, int gndPin)
{
  // first turn on the sensor
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  // now wait for 20seconds for the sensor to settle
  delay(20000);
  // now read the sensor value
  float measuredValue = (float(analogRead(sensorPin))/1023.0)*3.3;
  // turn off the sensor
  pinMode(gndPin, INPUT);
  return measuredValue;
}