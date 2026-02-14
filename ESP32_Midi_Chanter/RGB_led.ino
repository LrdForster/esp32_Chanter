#include <Adafruit_NeoPixel.h>
#include "RGB_led.h"
#include "config.h"

Adafruit_NeoPixel statusLED(
  1,
  PIN_STATUS_LED,
  NEO_GRB + NEO_KHZ800
);

void rgbLedSetup() {
  statusLED.begin();
  statusLED.clear();
  statusLED.show();
}

void setStatusLED(uint32_t colour) {
  statusLED.setPixelColor(0, colour);
  statusLED.show();
}
