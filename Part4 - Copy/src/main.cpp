#include <Arduino.h>

#include <wdt.h>
#include <epaper.h>
#include <waterpumpctrl.h>

// last time the sensors were measured, in milliseconds
unsigned long previousMillis = 0;
// for sensor measuring and possible pump interval
const long measuringInterval = 18000000; // 5 hour interval

// soil moisture sensors --> signals
int Pin1 = A0;
int Pin2 = A1;
int Pin3 = A2;
int Pin4 = A3;

// gnd connection through digital pins (can be turned on/off)
int SoilM1 = 6;
int SoilM2 = 12;
int SoilM3 = A4; // use this analog pin as digital pin (A0-A5 can be used as digital pins as well)
int SoilM4 = A5; // use this analog pin as digital pin

// water pumps to 4 channel relay
int In1 = 2;
int In2 = 3;
int In3 = 4;
int In4 = 5;

// measured values of soil humidity
float soilHumidity1 = 0.0;
float soilHumidity2 = 0.0;
float soilHumidity3 = 0.0;
float soilHumidity4 = 0.0;

int measurementNumber = 0;

void setup() {
  Serial.begin(9600);

  initDisplay();

  analogReference(EXTERNAL); // set the analog reference to 3.3V

  pinMode(Pin1, INPUT);
  pinMode(Pin2, INPUT);
  pinMode(Pin3, INPUT);
  pinMode(Pin4, INPUT);

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  digitalWrite(In1, HIGH);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, HIGH);

  pinMode(SoilM1, INPUT); // set all as input to turn off gnd connection --> soil moisture sensor is not consuming power
  pinMode(SoilM2, INPUT);
  pinMode(SoilM3, INPUT);
  pinMode(SoilM4, INPUT);

  setupWatchDogTimer();

  delay(500);
}

void loop() {
  Serial.println("Previous millis " + String(previousMillis));
  if (previousMillis >= measuringInterval
      || previousMillis == 0) { // if it's time to measure or first time of measuring
    previousMillis = 0; // reset the timer
    
    measurementNumber = measurementNumber + 1;

    // read sensor values, print them and water if necessary
    soilHumidity1 = calcSoilHumid(Pin1, SoilM1);
    String EpaperMsg1 = epaperMsg(soilHumidity1, 1, In1);
    soilHumidity2 = calcSoilHumid(Pin2, SoilM2);
    String EpaperMsg2 = epaperMsg(soilHumidity2, 2, In2);
    soilHumidity3 = calcSoilHumid(Pin3, SoilM3);
    String EpaperMsg3 = epaperMsg(soilHumidity3, 3, In3);
    soilHumidity4 = calcSoilHumid(Pin4, SoilM4);
    String EpaperMsg4 = epaperMsg(soilHumidity4, 4, In4);

    String measurement = "Measurement: " + String(measurementNumber);

    String msgComplete = 
    "\n" + measurement
    + "\n" + EpaperMsg1
    + "\n" + EpaperMsg2
    + "\n" + EpaperMsg3
    + "\n" + EpaperMsg4;

    const char* msg = msgComplete.c_str();
    writeToEPaper(msg);
    delay(1000); // wait 1 second so epaper can display message

    // now water, if necessary
    bool water1 = water(soilHumidity1, 1, In1);
    bool water2 = water(soilHumidity2, 2, In2);
    bool water3 = water(soilHumidity3, 3, In3);
    bool water4 = water(soilHumidity4, 4, In4);
  }
  Serial.println("Enter sleep mode for 8 seconds.");
  delay(100); // delay to get serial monitor output
  previousMillis = previousMillis + 8100; // 8.1 seconds - 8 seconds from WDT + 100ms delay
  enterSleep();  // deep sleep until WDT kicks
}