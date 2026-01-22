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
      return CRGB(255, 200, 150);
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
// RENDER LOOP
// ----------------------------------------------------------

void renderCity() {
  if (!leds || ledCount == 0) return;

  if (testModeEnabled) {
    renderTestPattern();
    return;
  }

  uint16_t buildingCount = getBuildingInstanceCount();

  for (uint16_t b = 0; b < buildingCount; b++) {
    const BuildingInstance* inst = getBuildingInstance(b);
    const BuildingDef* def = inst->def;

    for (uint16_t i = 0; i < def->led_count; i++) {
      uint16_t globalIndex = inst->led_offset + i;

      if (globalIndex >= ledCount) continue;

      leds[globalIndex] = colorForZone(def->leds[i].zone);
    }
  }

  FastLED.show();
}

// ----------------------------------------------------------
// TEST PATTERN
// ----------------------------------------------------------

static void renderTestPattern() {
  if (!leds || ledCount < 10) return;

  CRGB colors[3] = { CRGB::Red, CRGB::Green, CRGB::Blue };

  for (uint8_t i = 0; i < 10; i++) {
    leds[i] = colors[(i + testFrame) % 3];
  }

  testFrame++;
  FastLED.show();
}

void enableTestPattern(bool enable) {
  testModeEnabled = enable;
  testFrame = 0;

  FastLED.clear();
  FastLED.show();
}
