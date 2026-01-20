#pragma once

#include <Arduino.h>

/******************************************************************************
 * ZONE FLAGS
 *
 * These describe how a zone behaves.
 *****************************************************************************/
enum ZoneFlags : uint8_t {
  ZONE_FIXED     = 1 << 0,  // fixed color / behavior
  ZONE_AMBIENT   = 1 << 1,  // normal interior lighting
  ZONE_FEATURE   = 1 << 2,  // animated feature (signs, projector)
  ZONE_SEASONAL  = 1 << 3,  // affected by seasonal palettes
  ZONE_EXTERIOR  = 1 << 4   // outdoor lighting
};

/******************************************************************************
 * ZONE DEFINITION
 *
 * Zones are contiguous and ordered.
 * Order MUST match physical LED wiring order.
 *****************************************************************************/
struct ZoneDef {
  const char* name;   // zone identifier (e.g. "interior", "sign")
  uint16_t    count;  // number of LEDs in this zone
  uint8_t     flags;  // ZoneFlags bitmask
};

/******************************************************************************
 * BUILDING TYPE
 *
 * DESIGN RULE:
 * Each physical building has its own BuildingType and BuildingDef.
 *****************************************************************************/
enum BuildingType {
  BUILDING_MOVIE_THEATER
  // Add new building types here
};

/******************************************************************************
 * BUILDING DEFINITION
 *****************************************************************************/
struct BuildingDef {
  BuildingType  type;       // unique building identifier
  const char*   name;       // MQTT / layout name
  uint16_t      ledCount;   // derived from zones
  const ZoneDef* zones;     // ordered zone list
  uint8_t       zoneCount;  // number of zones
};

/******************************************************************************
 * COMPILE-TIME / BUILD-TIME HELPERS
 *****************************************************************************/

// Number of zones in a ZoneDef array
#define ZONE_COUNT(zones) (sizeof(zones) / sizeof(zones[0]))

// LED count helper
// NOTE:
// - Cannot be constexpr in C++11 due to loop restrictions
// - Will be constant-folded by the compiler for static data
// - Zero meaningful runtime cost on ESP32
template <size_t N>
inline uint16_t ledCountFromZones(const ZoneDef (&zones)[N]) {
  uint16_t total = 0;
  for (size_t i = 0; i < N; i++) {
    total += zones[i].count;
  }
  return total;
}

// Public macro used by building definitions
#define LED_COUNT(zones) ledCountFromZones(zones)

/******************************************************************************
 * BUILDING REGISTRY (defined in building_registry.cpp)
 *****************************************************************************/
extern const BuildingDef* ALL_BUILDINGS[];
extern const uint8_t BUILDING_COUNT;

/******************************************************************************
 * BUILDING LOOKUP HELPERS
 *****************************************************************************/
const BuildingDef* getBuildingDefByName(const String& name);
