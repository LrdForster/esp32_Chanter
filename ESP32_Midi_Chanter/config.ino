#include "config.h"

// ================= GPIO Pin Configuration =================
const uint8_t PIN_BUTTON  = 2;

const uint8_t PIN_TOUCH_1      = 4;
const uint8_t PIN_TOUCH_2      = 5;
const uint8_t PIN_TOUCH_3      = 6;
const uint8_t PIN_TOUCH_4      = 7;
const uint8_t PIN_TOUCH_5      = 8;
const uint8_t PIN_TOUCH_6      = 9;
const uint8_t PIN_TOUCH_7      = 10;
const uint8_t PIN_TOUCH_8      = 11;

const uint8_t Bat_Low      = 12;


const uint8_t PIN_DAC_DRONE    = 13;
//const uint8_t PIN_DAC_CHANTER  = 18;

const uint8_t PIN_STATUS_LED   = 48;

// ---------------- MP3 Sample Files ----------------
const char* INSTRUMENT_1_SAMPLES[2] = {
  "instr1_note1.mp3",
  "instr1_note2.mp3"
};

const char* INSTRUMENT_2_SAMPLES[2] = {
  "instr2_note1.mp3",
  "instr2_note2.mp3"
};



// =====================================================
// RGB LED COLOUR DEFINITIONS
// Simple, high-contrast, user-friendly colours
// =====================================================

// NeoPixel colour constants (GRB handled internally)
const uint32_t LED_RED     = 0xFF0000;
const uint32_t LED_GREEN   = 0x00FF00;
const uint32_t LED_BLUE    = 0x0000FF;

const uint32_t LED_YELLOW  = 0xFFFF00;
const uint32_t LED_CYAN    = 0x00FFFF;
const uint32_t LED_PURPLE  = 0x800080;

const uint32_t LED_ORANGE  = 0xFF8000;
const uint32_t LED_PINK    = 0xB45078;

const uint32_t LED_WHITE   = 0xFFFFFF;
const uint32_t LED_OFF     = 0x000000;




// ================= WiFi / OTA =================
const char* HOST_NAME     = "My_ESP32_Chanter_01";
