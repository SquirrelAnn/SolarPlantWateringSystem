#include "epaper.h"
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

using namespace EpaperDisplay;

#define MAX_DISPLAY_BUFFER_SIZE 800
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_BW<GxEPD2_290_GDEY029T94, MAX_HEIGHT(GxEPD2_290_GDEY029T94)> display(GxEPD2_290_GDEY029T94(/*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEY029T94  128x296, SSD1680, (FPC-A005 20.06.15)

// E paper settings for Arduino Nano or Uno
// BUSY -> D7
// RST -> D9
// DC -> D8
// CS -> D10
// CLK -> D13
// DIN -> D11
// GND -> GND
// 3.3V -> 3.3V

void epaperDisplay::initDisplay(){
  display.init();
}

void epaperDisplay::writeToEPaper(const char* msg){
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(msg, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(msg);
  }
  while (display.nextPage());
  display.hibernate(); // turns powerOff() and sets controller to deep sleep for minimum power use, ONLY if wakeable by RST (rst >= 0)
}