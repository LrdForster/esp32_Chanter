#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel statusLED(1, 48, NEO_GRB + NEO_KHZ800);

const int touchPins[] = {4, 5, 6, 7, 8, 9, 10, 11};
const int buttonPin = 12;
const int outputPin = 3;

const uint32_t colors[] = {
  statusLED.Color(255, 0, 0),   // Red
  statusLED.Color(0, 0, 255),   // Blue
  statusLED.Color(0, 255, 0),   // Green
  statusLED.Color(255, 0, 255)  // Purple
};

int baseline[8];

void setup() {
  statusLED.begin();
  statusLED.setBrightness(50);
  statusLED.show();

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(outputPin, OUTPUT);

  // 2 second delay
  delay(2000);

  // Measure 8 touch values (untouched)
  for (int i = 0; i < 8; i++) {
    baseline[i] = touchRead(touchPins[i]);
  }

  // 1 second delay
  delay(1000);

  // Measure lowest of 8 and output frequency until first button press
  while (digitalRead(buttonPin) == HIGH) {
    int lowestRead = touchRead(touchPins[0]);
    for (int j = 1; j < 8; j++) {
      int currentRead = touchRead(touchPins[j]);
      if (currentRead < lowestRead) {
        lowestRead = currentRead;
      }
    }
    tone(outputPin, (long)lowestRead * 10);
  }

  // Debounce and stop tone to enter main loop
  noTone(outputPin);
  delay(300);
  while (digitalRead(buttonPin) == LOW);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    statusLED.setPixelColor(0, colors[i % 4]);
    statusLED.show();

    // Measure specific pin (4, then 5, etc.) and output frequency
    while (digitalRead(buttonPin) == HIGH) {
      long freq = (long)touchRead(touchPins[i]) * 10;
      tone(outputPin, freq);
    }

    noTone(outputPin);
    statusLED.setPixelColor(0, 0);
    statusLED.show();
    
    // Debounce/Wait for release
    delay(300); 
    while (digitalRead(buttonPin) == LOW);
  }
}
