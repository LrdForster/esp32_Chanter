#pragma once
#include <stdint.h>

// ================= GPIO Pin Configuration =================
extern const uint8_t PIN_BUTTON;

extern const uint8_t PIN_TOUCH_1;
extern const uint8_t PIN_TOUCH_2;
extern const uint8_t PIN_TOUCH_3;
extern const uint8_t PIN_TOUCH_4;
extern const uint8_t PIN_TOUCH_5;
extern const uint8_t PIN_TOUCH_6;
extern const uint8_t PIN_TOUCH_7;
extern const uint8_t PIN_TOUCH_8;

extern const uint8_t PIN_DAC_DRONE;
//extern const uint8_t PIN_DAC_CHANTER;

extern const uint8_t BAT_LOW;

extern const uint8_t PIN_STATUS_LED;

// ---------------- MP3 Sample Files ----------------
// Max 2 samples per instrument for now
extern const char* INSTRUMENT_1_SAMPLES[2];
extern const char* INSTRUMENT_2_SAMPLES[2];

// ================= WiFi / OTA =================
#include "secrets.h"
extern const char* HOST_NAME;
