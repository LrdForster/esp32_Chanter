#include <Arduino.h>
#include "config.h"
#include "ota_update.h"
#include "boot_select.h"
#include "main_app.h"

bool otaMode = false;

void setup() {
  Serial.begin(115200);

  otaMode = isOTAModeRequested();

  if (otaMode) {
    otaSetup();
  } else {
    mainAppSetup();
  }
}

void loop() {
  if (otaMode) {
    otaLoop();
  } else {
    mainAppLoop();
  }
}
