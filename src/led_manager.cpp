#include "led_manager.h"

#include <FastLED.h>

#include "config.h"
#include "city_layout.h"
#include "building_defs.h"

// ----------------------------------------------------------
// INTERNAL STATE
// ----------------------------------------------------------

static CRGB* leds = nullptr;
static uint16_t ledCount = 0;

// ----------------------------------------------------------
// INITIALIZATION
// ----------------------------------------------------------

void initLedManager(uint16_t total_leds) {
  ledCount = total_leds;

  if (leds) {
    delete[] leds;
  }

  leds = new CRGB[ledCount];

  FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(leds, ledCount);
  FastLED.setBrightness(LED_BRIGHTNESS);

  FastLED.clear();
  FastLED.show();
}

// ----------------------------------------------------------
// COLOR SELECTION (TEMPORARY / DEBUG)
// ----------------------------------------------------------

static CRGB colorForZone(ZoneType zone) {
  switch (zone) {
    case ZONE_STREET:
      return CRGB(255, 200, 150);   // warm white
    case ZONE_INTERIOR:
      return CRGB(255, 180, 110);   // interior warm
    case ZONE_SIGNAGE:
      return CRGB::Red;             // signage
    case ZONE_PROJECTOR:
      return CRGB::Blue;            // projector
    default:
      return CRGB::Black;
  }
}

// ----------------------------------------------------------
// RENDER LOOP
// ----------------------------------------------------------

void renderCity() {
  if (!leds || ledCount == 0) {
    return;
  }

  uint16_t buildingCount = getBuildingInstanceCount();

  for (uint16_t b = 0; b < buildingCount; b++) {
    const BuildingInstance* inst = getBuildingInstance(b);
    const BuildingDef* def = inst->def;

    for (uint16_t i = 0; i < def->led_count; i++) {
      uint16_t globalIndex = inst->led_offset + i;

      if (globalIndex >= ledCount) {
        continue;
      }

      const LedDef& led = def->leds[i];
      leds[globalIndex] = colorForZone(led.zone);
    }
  }

  FastLED.show();
}
