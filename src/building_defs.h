#pragma once

#include <stdint.h>

/************************************************************
 * ZONE TYPES
 * Physical / logical classification of LEDs
 ************************************************************/
enum ZoneType : uint8_t {
  ZONE_STREET,
  ZONE_INTERIOR,
  ZONE_SIGNAGE,
  ZONE_PROJECTOR
};

/************************************************************
 * ZONE / LED FLAGS
 * Behavioral traits (bitmask)
 ************************************************************/
enum ZoneFlags : uint8_t {
  ZF_NONE      = 0,
  ZF_EXTERIOR  = 1 << 0,
  ZF_AMBIENT   = 1 << 1,
  ZF_SEASONAL  = 1 << 2,
  ZF_FEATURE   = 1 << 3
};

/************************************************************
 * PER-LED DEFINITION
 * One entry per physical LED, order matters
 ************************************************************/
struct LedDef {
  ZoneType zone;
  uint8_t flags;
};

/************************************************************
 * BUILDING DEFINITION
 ************************************************************/
struct BuildingDef {
  const char* id;          // e.g. "MOVIE_THEATER"
  uint16_t led_count;      // number of LEDs in this building
  const LedDef* leds;      // pointer to per-LED definitions
};
