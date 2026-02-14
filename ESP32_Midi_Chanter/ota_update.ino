#include <WiFi.h>
#include <ArduinoOTA.h>
#include "config.h"   // your WIFI_SSID, WIFI_PASSWORD, HOST_NAME, PIN_STATUS_LED

// ---------------- OTA timeout configuration ----------------
const unsigned long OTA_TIMEOUT = 5UL * 60UL * 1000UL; // 5 minutes in milliseconds
unsigned long otaStartTime = 0;
bool otaActive = false;

// ---------------- OTA Setup ----------------
void otaSetup() {
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  pinMode(PIN_STATUS_LED, OUTPUT);

  // Blink LED while connecting
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(PIN_STATUS_LED, !digitalRead(PIN_STATUS_LED));
    delay(300);
  }
  digitalWrite(PIN_STATUS_LED, HIGH); // steady ON when connected

  // Initialize Arduino OTA
  ArduinoOTA.setHostname(HOST_NAME);
  // Optional: set OTA password
   ArduinoOTA.setPassword("Password");

  // LED feedback during OTA
  ArduinoOTA.onStart([]() {
    digitalWrite(PIN_STATUS_LED, HIGH);  // LED ON while OTA active
  });
  ArduinoOTA.onEnd([]() {
    digitalWrite(PIN_STATUS_LED, LOW);   // LED OFF after OTA upload
  });

  ArduinoOTA.begin();  // starts OTA service

  otaStartTime = millis();
  otaActive = true;
}

// ---------------- OTA Loop ----------------
void otaLoop() {
  ArduinoOTA.handle();  // must be called continuously

  // Optional: blink LED slowly while waiting for OTA
  static unsigned long lastBlink = 0;
  static bool ledState = true;
  if (otaActive && millis() - lastBlink > 1000) {
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(PIN_STATUS_LED, ledState ? HIGH : LOW);
  }

  // Check OTA timeout
  if (otaActive && millis() - otaStartTime > OTA_TIMEOUT) {
    otaActive = false;

    // Option 1: Reset to main app
    ESP.restart();

    // Option 2: Power down battery if you have a control pin
    // digitalWrite(BATTERY_SWITCH_PIN, LOW);
  }
}
