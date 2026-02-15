#include <Adafruit_NeoPixel.h>

#define ADC_PIN     12
#define LED_PIN     48
#define LED_COUNT   1

#define ADC_THRESHOLD 2950   // <-- change if needed

Adafruit_NeoPixel pixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  // ADC setup
  analogReadResolution(12);
  analogSetPinAttenuation(ADC_PIN, ADC_11db);

  // NeoPixel setup
  pixel.begin();
  pixel.setBrightness(128); // 50%
  pixel.clear();
  pixel.show();

  // Let RC network settle
  delay(1000);
}

void loop() {
  int adcValue = analogRead(ADC_PIN);

  Serial.println(adcValue);

  if (adcValue < ADC_THRESHOLD) {
    // LOW battery -> RED
    pixel.setPixelColor(0, pixel.Color(255, 0, 0));
  } else {
    // OK -> GREEN
    pixel.setPixelColor(0, pixel.Color(0, 255, 0));
  }

  pixel.show();
  delay(1000);
}