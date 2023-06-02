#include <Arduino.h>

// last time the sensors were measured, in milliseconds
unsigned long previousMillis = 0;
// for sensor measuring and possible pump interval
const long measuringInterval = 5000; // 5 seconds

// E paper settings for Arduino Nano or Uno
// BUSY -> D7
// RST -> D9
// DC -> D8
// CS -> D10
// CLK -> D13
// DIN -> D11
// GND -> GND
// 3.3V -> 3.3V

// soil moisture sensors
int Pin1 = A0;
int Pin2 = A1;
int Pin3 = A2;
int Pin4 = A3;

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

void setup() {
  Serial.begin(9600);

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
}

bool water(int pumpNumber)
{
  digitalWrite(pumpNumber, LOW); // turn on pump
  delay(30000); // 30 seconds of watering
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
  if (sensorValue >= 2.3 && sensorValue <= 2.75){
    Serial.println("Watering...");
    water(pumpNumber);
    return "Watering";
  } else {
    Serial.println("No watering needed");
    return "No watering needed";
  }
}

float calcSoilHumid(int sensorPin){
  return (float(analogRead(sensorPin))/1023.0)*3.3;
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= measuringInterval
      || previousMillis == 0) { // if it's time to measure or first time of measuring
    previousMillis = currentMillis;

    // read sensor values, print them and water if necessary
    soilHumidity1 = calcSoilHumid(Pin1);
    pumpIfDry(soilHumidity1, 1, In1);

    soilHumidity2 = calcSoilHumid(Pin2);
    pumpIfDry(soilHumidity2, 2, In2);

    soilHumidity3 = calcSoilHumid(Pin3);
    pumpIfDry(soilHumidity3, 3, In3);

    soilHumidity4 = calcSoilHumid(Pin4);
    pumpIfDry(soilHumidity4, 4, In4);
  }
}