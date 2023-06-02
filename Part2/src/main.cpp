#include <Arduino.h>

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define MAX_DISPLAY_BUFFER_SIZE 800
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
//GxEPD2_BW<GxEPD2_290, MAX_HEIGHT(GxEPD2_290)> display(GxEPD2_290(/*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEH029A1 128x296, SSD1608 (IL3820)
//GxEPD2_BW<GxEPD2_290_T5, MAX_HEIGHT(GxEPD2_290_T5)> display(GxEPD2_290_T5(/*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEW029T5 128x296, UC8151 (IL0373)
//GxEPD2_BW<GxEPD2_290_T5D, MAX_HEIGHT(GxEPD2_290_T5D)> display(GxEPD2_290_T5D(/*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEW029T5D 128x296, UC8151D
//GxEPD2_BW<GxEPD2_290_I6FD, MAX_HEIGHT(GxEPD2_290_I6FD)> display(GxEPD2_290_I6FD(/*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEW029I6FD 128x296, UC8151D
//GxEPD2_BW<GxEPD2_290_T94, MAX_HEIGHT(GxEPD2_290_T94)> display(GxEPD2_290_T94(/*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEM029T94 128x296, SSD1680
//GxEPD2_BW<GxEPD2_290_T94_V2, MAX_HEIGHT(GxEPD2_290_T94_V2)> display(GxEPD2_290_T94_V2(/*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEM029T94 128x296, SSD1680, Waveshare 2.9" V2 variant
//GxEPD2_BW<GxEPD2_290_BS, MAX_HEIGHT(GxEPD2_290_BS)> display(GxEPD2_290_BS(/*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // DEPG0290BS 128x296, SSD1680
//GxEPD2_BW<GxEPD2_290_M06, MAX_HEIGHT(GxEPD2_290_M06)> display(GxEPD2_290_M06(/*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEW029M06  128x296, UC8151D
GxEPD2_BW<GxEPD2_290_GDEY029T94, MAX_HEIGHT(GxEPD2_290_GDEY029T94)> display(GxEPD2_290_GDEY029T94(/*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEY029T94  128x296, SSD1680, (FPC-A005 20.06.15)


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

const char HelloWorld[] = "Hello World!";

void setup() {
  Serial.begin(9600);

  display.init();
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
  display.hibernate();

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
  if (sensorValue >= 5.3 && sensorValue <= 2.75){
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