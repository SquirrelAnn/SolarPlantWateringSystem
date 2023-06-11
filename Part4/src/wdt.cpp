#include "wdt.h"
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <Arduino.h>

using namespace SleepControl;

// Watchdog Interrupt Service. This is executed when watchdog timed out.
ISR(WDT_vect) {
	
}

// Enters the arduino into sleep mode.
void wdtControl::enterSleep(void) {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // SLEEP_MODE_PWR_DOWN for lowest power consumption.
  sleep_enable();
  
  sleep_mode();
  
  // The program will continue from here after the WDT timeout
  sleep_disable(); // disable sleep
  
  /* Re-enable the peripherals. */
  power_all_enable();
}

// Setup the Watch Dog Timer (WDT)
void wdtControl::setupWatchDogTimer() {
	 /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);
  
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  /* set new watchdog timeout prescaler value */
  WDTCSR = 1<<WDP0 | 1<<WDP3; /* 8.0 seconds */
  
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
}