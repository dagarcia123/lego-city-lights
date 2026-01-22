#pragma once

#include <stdint.h>

/************************************************************
 * ZONE TYPES
 ************************************************************/
enum ZoneType : uint8_t {
  ZONE_STREET,
  ZONE_INTERIOR,
  ZONE_SIGNAGE,
  ZONE_PROJECTOR
};

/************************************************************
 * ZONE FLAGS (BITMASK)
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
 ************************************************************/
struct LedDef {
  ZoneType zone;
  uint8_t flags;
};

/************************************************************
 * BUILDING DEFINITION
 ************************************************************/
struct BuildingDef {
  const char* id;
  uint16_t led_count;
  const LedDef* leds;
};
