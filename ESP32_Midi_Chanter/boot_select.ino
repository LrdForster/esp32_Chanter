#include "boot_select.h"
#include "config.h"
#include <Arduino.h>

bool isOTAModeRequested() {
  // Configure button pin
  pinMode(PIN_BUTTON, INPUT);

  // Small delay to stabilize after reset
  delay(50);

  // Button LOW at boot = OTA requested
  return (digitalRead(PIN_BUTTON) == LOW);
}
