// ESP32-S3 Super Mini - 440Hz Tone Generator using LEDC
// Pin 13: Audio Out
// Pin 2: Button (Active Low with Internal Pullup)

// Pin definitions
#define BUTTON_PIN 2
#define AUDIO_PIN 13

// Audio configuration
#define SAMPLE_RATE 44100
#define TONE_FREQ 440.0f
#define AMPLITUDE 127  // 0-255 range for 8-bit output
#define LEDC_RESOLUTION 8  // 8-bit resolution

// State variables
volatile bool toneEnabled = true;
TaskHandle_t audioTaskHandle = NULL;
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// Pre-calculated sine wave lookup table (256 samples)
uint8_t sineTable[256];
volatile uint16_t sampleIndex = 0;
volatile uint32_t phaseAccumulator = 0;
uint32_t phaseIncrement;

// ISR for button press
void IRAM_ATTR buttonISR() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Button pressed - stop tone
    toneEnabled = false;
  } else {
    // Button released - start tone
    toneEnabled = true;
  }
}

// Timer ISR - generates audio samples at sample rate
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  
  if (toneEnabled) {
    // Update phase accumulator
    phaseAccumulator += phaseIncrement;
    
    // Get table index from upper 8 bits of accumulator
    uint8_t index = (phaseAccumulator >> 24) & 0xFF;
    
    // Output sample via LEDC
    ledcWrite(AUDIO_PIN, sineTable[index]);
  } else {
    // Output silence (middle value for DC offset)
    ledcWrite(AUDIO_PIN, 128);
  }
  
  portEXIT_CRITICAL_ISR(&timerMux);
}

// Task running on Core 1 (can be used for other audio processing)
void audioTask(void *parameter) {
  while (true) {
    // This task can be used for envelope control, effects, etc.
    // For now, just keep it alive
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("ESP32-S3 Tone Generator Starting...");
  
  // Configure button with internal pullup
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, CHANGE);
  
  // Generate sine wave lookup table
  for (int i = 0; i < 256; i++) {
    sineTable[i] = (uint8_t)(128 + (sin(2.0 * PI * i / 256.0) * AMPLITUDE));
  }
  
  // Calculate phase increment for 440Hz
  // phaseIncrement = (frequency * 2^32) / sample_rate
  phaseAccumulator = 0;
  phaseIncrement = (uint32_t)((TONE_FREQ * 4294967296.0) / SAMPLE_RATE);
  
  // Configure LEDC for PWM audio output (new API)
  ledcAttach(AUDIO_PIN, SAMPLE_RATE, LEDC_RESOLUTION);
  ledcWrite(AUDIO_PIN, 128);  // Set to middle value initially
  
  // Configure hardware timer for sample rate (new API)
  timer = timerBegin(SAMPLE_RATE);  // Create timer at sample rate frequency
  timerAttachInterrupt(timer, &onTimer);  // Attach ISR
  timerAlarm(timer, 1, true, 0);  // Alarm every 1 tick, auto-reload, unlimited
  
  Serial.println("Audio configured");
  
  // Create audio task pinned to Core 1
  xTaskCreatePinnedToCore(
    audioTask,          // Task function
    "AudioTask",        // Task name
    2048,              // Stack size
    NULL,              // Parameters
    1,                 // Priority
    &audioTaskHandle,  // Task handle
    1                  // Core 1
  );
  
  Serial.println("Audio task started on Core 1");
  Serial.println("Press button to mute, release to unmute");
}

void loop() {
  // Core 0 remains free
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}