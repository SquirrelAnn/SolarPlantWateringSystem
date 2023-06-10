#include <Arduino.h>

void water(int pumpNumber)
{
  digitalWrite(pumpNumber, LOW); // turn on pump
  delay(20000); // 20 seconds of watering (30s ~ 1Liter of water)
  digitalWrite(pumpNumber, HIGH); // turn off pump
}

String pumpIfDry(float sensorValue, int sensorNumber, int pumpNumber){
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
    water(pumpNumber);
    String waterMsg = " 20s Watering.";
    String returnMsg = pumpNo + (pumpNumber - 1) + ":" + sensorValue + waterMsg;
    return returnMsg;
  } else {
    String waterMsg = " No watering.";
    String returnMsg = pumpNo + (pumpNumber - 1) + ":" + sensorValue + waterMsg;
    return returnMsg;
  }
}

float calcSoilHumid(int sensorPin){
  return (float(analogRead(sensorPin))/1023.0)*3.3;
}