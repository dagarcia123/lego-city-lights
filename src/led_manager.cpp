#include "led_manager.h"
#include "config.h"

#ifdef DEBUG_SERIAL
#include <Arduino.h>
#endif

// -----------------------------
// Internal state
// -----------------------------
static CRGB leds[MAX_LEDS];
static uint16_t ledCount = MAX_LEDS;   // will later be set dynamically
static uint8_t globalBrightness = DEFAULT_BRIGHTNESS;
static bool powerOn = true;

// -----------------------------
// Init
// -----------------------------
void initLEDs() {
  FastLED.addLeds<LED_TYPE, LED_DATA_PIN, LED_COLOR>(leds, ledCount);
  FastLED.setBrightness(globalBrightness);
  FastLED.clear(true);

#ifdef DEBUG_SERIAL
  Serial.print("LED system initialized, max LEDs: ");
  Serial.println(ledCount);
#endif
}

// -----------------------------
// Render
// -----------------------------
void renderLEDs() {
  if (!powerOn) {
    FastLED.clear(false);
    FastLED.show();
    return;
  }

  FastLED.setBrightness(globalBrightness);
  FastLED.show();
}

// -----------------------------
// Global controls
// -----------------------------
void setGlobalBrightness(uint8_t brightness) {
  globalBrightness = brightness;

#ifdef DEBUG_SERIAL
  Serial.print("Brightness set to ");
  Serial.println(brightness);
#endif
}

void setPowerState(bool on) {
  powerOn = on;

#ifdef DEBUG_SERIAL
  Serial.print("Power state: ");
  Serial.println(on ? "ON" : "OFF");
#endif
}

// -----------------------------
// LED access
// -----------------------------
CRGB* getLEDArray() {
  return leds;
}

uint16_t getLEDCount() {
  return ledCount;
}
