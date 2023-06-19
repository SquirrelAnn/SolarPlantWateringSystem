#include <Arduino.h>

#include "wdt.h"
#include "epaper.h"
#include "waterpumpctrl.h"

// last time the sensors were measured, in milliseconds
unsigned long elapsedTime = 0;
// for sensor measuring and possible pump interval
const long measuringInterval = 18000000; // 5 hour interval

// soil moisture sensors --> signals
int SensorSignal1 = A4;
int SensorSignal2 = A5;
int SensorSignal3 = A6;
int SensorSignal4 = A7;

// gnd connection through digital pins (can be turned on/off)
int SoilM1 = 6; // gnd sensor 1
int SoilM2 = A0; // gnd sensor 2
int SoilM3 = A1; // gnd sensor 3 use this analog pin as digital pin (A0-A5 can be used as digital pins as well)
int SoilM4 = A2; // gnd sensor 4 use this analog pin as digital pin

// water pumps to 4 channel relay
int Pump1 = 2;
int Pump2 = 3;
int Pump3 = 4;
int Pump4 = 5;

// measured values of soil humidity
float soilHumidity1 = 0.0;
float soilHumidity2 = 0.0;
float soilHumidity3 = 0.0;
float soilHumidity4 = 0.0;

int measurementNumber = 0;

EpaperDisplay::epaperDisplay epaper;
WaterPumpCtrl::waterPumpCtrl waterPumpCtrl;
SleepControl::wdtControl wdtControl;

void setup() {
  Serial.begin(9600);
  epaper.initDisplay();

  analogReference(EXTERNAL); // set the analog reference to 3.3V

  pinMode(SensorSignal1, INPUT);
  pinMode(SensorSignal2, INPUT);
  pinMode(SensorSignal3, INPUT);
  pinMode(SensorSignal4, INPUT);

  pinMode(Pump1, OUTPUT);
  pinMode(Pump2, OUTPUT);
  pinMode(Pump3, OUTPUT);
  pinMode(Pump4, OUTPUT);

  digitalWrite(Pump1, HIGH);
  digitalWrite(Pump2, HIGH);
  digitalWrite(Pump3, HIGH);
  digitalWrite(Pump4, HIGH);

  pinMode(SoilM1, INPUT); // set all as input to turn off gnd connection --> soil moisture sensor is not consuming power
  pinMode(SoilM2, INPUT);
  pinMode(SoilM3, INPUT);
  pinMode(SoilM4, INPUT);

  wdtControl.setupWatchDogTimer();

  delay(500);
}

void loop() {
  Serial.println("Previous millis " + String(elapsedTime));
  if (elapsedTime >= measuringInterval
      || elapsedTime == 0) { // if it's time to measure or first time of measuring
    elapsedTime = 0; // reset the timer

    measurementNumber = measurementNumber + 1;

    // read sensor values, print them and water if necessary
    soilHumidity1 = waterPumpCtrl.calcSoilHumid(SensorSignal1, SoilM1);
    String EpaperMsg1 = waterPumpCtrl.epaperMsg(soilHumidity1, 1, Pump1);
    soilHumidity2 = waterPumpCtrl.calcSoilHumid(SensorSignal2, SoilM2);
    String EpaperMsg2 = waterPumpCtrl.epaperMsg(soilHumidity2, 2, Pump2);
    soilHumidity3 = waterPumpCtrl.calcSoilHumid(SensorSignal3, SoilM3);
    String EpaperMsg3 = waterPumpCtrl.epaperMsg(soilHumidity3, 3, Pump3);
    soilHumidity4 = waterPumpCtrl.calcSoilHumid(SensorSignal4, SoilM4);
    String EpaperMsg4 = waterPumpCtrl.epaperMsg(soilHumidity4, 4, Pump4);

    String measurement = "Measurement: " + String(measurementNumber);

    String msgComplete = 
    "\n" + measurement
    + "\n" + EpaperMsg1
    + "\n" + EpaperMsg2
    + "\n" + EpaperMsg3
    + "\n" + EpaperMsg4;

    const char* msg = msgComplete.c_str();
    epaper.writeToEPaper(msg);
    delay(1000); // wait 1 second so epaper can display message

    // now water, if necessary
    bool water1 = waterPumpCtrl.water(soilHumidity1, 1, Pump1);
    bool water2 = waterPumpCtrl.water(soilHumidity2, 2, Pump2);
    bool water3 = waterPumpCtrl.water(soilHumidity3, 3, Pump3);
    bool water4 = waterPumpCtrl.water(soilHumidity4, 4, Pump4);
  }
  Serial.println("Enter sleep mode for 8 seconds.");
  delay(100); // delay to get serial monitor output
  elapsedTime = elapsedTime + 8100; // 8.1 seconds - 8 seconds from WDT + 100ms delay
  wdtControl.enterSleep();  // deep sleep until WDT kicks
}