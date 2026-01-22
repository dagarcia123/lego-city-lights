#include "led_manager.h"

#include <Arduino.h>
#include <FastLED.h>

#include "config.h"
#include "city_layout.h"
#include "building_defs.h"

// ----------------------------------------------------------
// TEST MODE STATE
// ----------------------------------------------------------

static bool testModeEnabled = false;
static uint8_t testFrame = 0;

// ----------------------------------------------------------
// INTERNAL STATE
// ----------------------------------------------------------

static CRGB* leds = nullptr;
static uint16_t ledCount = 0;

// ----------------------------------------------------------
// FORWARD DECLARATIONS (PRIVATE)
// ----------------------------------------------------------

static void renderTestPattern();
static CRGB colorForZone(ZoneType zone);

// ----------------------------------------------------------
// INITIALIZATION
// ----------------------------------------------------------

void initLedManager(uint16_t total_leds) {
  Serial.println("[LED] initLedManager() called");

  ledCount = total_leds;

  if (leds) {
    Serial.println("[LED] Reinitializing LEDs (deleting old buffer)");
    delete[] leds;
  }

  leds = new CRGB[ledCount];

  FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(leds, ledCount);
  FastLED.setBrightness(LED_BRIGHTNESS);

  FastLED.clear();
  FastLED.show();

  Serial.print("[LED] Initialized ");
  Serial.print(ledCount);
  Serial.println(" LEDs");
}

// ----------------------------------------------------------
// COLOR SELECTION (DEBUG / BASELINE)
// ----------------------------------------------------------

static CRGB colorForZone(ZoneType zone) {
  switch (zone) {
    case ZONE_STREET:
      // return CRGB(255, 200, 150);
      return CRGB::Yellow;
    case ZONE_INTERIOR:
      return CRGB(255, 180, 110);
    case ZONE_SIGNAGE:
      return CRGB::Red;
    case ZONE_PROJECTOR:
      return CRGB::Blue;
    default:
      return CRGB::Black;
  }
}
// ----------------------------------------------------------
// HELPER FUNCTIONS
// ----------------------------------------------------------
static uint8_t twinklePhase = 0;


static uint8_t twinkleBrightness(uint8_t base, uint16_t index) {
  // simple wave offset per LED
  uint8_t phase = twinklePhase + (index * 17);
  uint8_t wave = sin8(phase);          // 0–255
  uint8_t delta = scale8(wave, 40);    // max +/- ~40
  return qadd8(base - 20, delta);       // clamp-safe
}

// ----------------------------------------------------------
// RENDER LOOP
// ----------------------------------------------------------

void renderCity() {
  if (!leds || ledCount == 0) return;

  // ----------------------------------------------------------
  // TEST MODE OVERRIDE
  // ----------------------------------------------------------
  if (testModeEnabled) {
    renderTestPattern();
    return;
  }

  else {
    uint16_t buildingCount = getBuildingInstanceCount();

    for (uint16_t b = 0; b < buildingCount; b++) {
      const BuildingInstance* inst = getBuildingInstance(b);
      const BuildingDef* def = inst->def;

      for (uint16_t i = 0; i < def->led_count; i++) {
        uint16_t globalIndex = inst->led_offset + i;
        if (globalIndex >= ledCount) continue;

        const LedDef& led = def->leds[i];

        // Base color by zone
        CRGB color = colorForZone(led.zone);

        // ------------------------------------------------------
        // AMBIENT TWINKLE EFFECT
        // ------------------------------------------------------
        if ((led.flags & ZF_AMBIENT) && led.zone == ZONE_INTERIOR) {
          uint8_t phase = twinklePhase + (globalIndex * 17);
          uint8_t wave  = sin8(phase);          // 0–255
          uint8_t delta = scale8(wave, 40);     // max ±40
          uint8_t b     = qadd8(LED_BRIGHTNESS - 20, delta);
          color.nscale8_video(b);
        }

        leds[globalIndex] = color;
      }
    }

    // Advance twinkle animation
    twinklePhase++;

    FastLED.show();
  }
}


// ----------------------------------------------------------
// TEST PATTERN
// ----------------------------------------------------------

static void renderTestPattern() {
  for (uint16_t i = 0; i < ledCount; i++) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
}

void enableTestPattern(bool enable) {
  testModeEnabled = enable;
  testFrame = 0;

  FastLED.clear();
  FastLED.show();
}