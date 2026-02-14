#include "main_app.h"
#include "config.h"
#include "RGB_led.h"

// --------------------------------------------------
// Main Application Setup
// --------------------------------------------------
void mainAppSetup() {
  // Initialise RGB status LED hardware
  rgbLedSetup();

  // Start with LED off
  setStatusLED(LED_OFF);
}

// --------------------------------------------------
// Main Application Loop
// --------------------------------------------------
void mainAppLoop() {

  // Cycle through Red → Green → Blue
  setStatusLED(LED_RED);
  delay(3000);

  setStatusLED(LED_GREEN);
  delay(1000);

  setStatusLED(LED_BLUE);
  delay(3000);

    setStatusLED(LED_WHITE);
  delay(1000);
}
