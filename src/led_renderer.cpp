#include "led_renderer.h"

#include <FastLED.h>

#include "config.h"
#include "city_layout.h"
#include "building_defs.h"

static CRGB* leds = nullptr;
static uint16_t ledCount = 0;

void initLedRenderer(uint16_t total_leds) {
  ledCount = total_leds;
  leds = new CRGB[ledCount];

  FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(leds, ledCount);
  FastLED.setBrightness(LED_BRIGHTNESS);

  FastLED.clear();
  FastLED.show();
}

static CRGB colorForZone(ZoneType zone) {
  switch (zone) {
    case ZONE_STREET:
      return CRGB(255, 200, 150);
    case ZONE_INTERIOR:
      return CRGB(255, 180, 100);
    case ZONE_SIGNAGE:
      return CRGB::Red;
    case ZONE_PROJECTOR:
      return CRGB::Blue;
    default:
      return CRGB::Black;
  }
}

void renderCity() {
  uint16_t buildingCount = getBuildingInstanceCount();

  for (uint16_t b = 0; b < buildingCount; b++) {
    const BuildingInstance* inst = getBuildingInstance(b);
    const BuildingDef* def = inst->def;

    for (uint16_t i = 0; i < def->led_count; i++) {
      uint16_t globalIndex = inst->led_offset + i;
      leds[globalIndex] = colorForZone(def->leds[i].zone);
    }
  }

  FastLED.show();
}
