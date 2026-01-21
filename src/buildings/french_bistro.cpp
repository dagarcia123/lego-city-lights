#include "building_defs.h"

static const LedDef FRENCH_BISTRO_LEDS[] = {
  { ZONE_STREET, ZF_EXTERIOR },
  { ZONE_STREET, ZF_EXTERIOR },
  { ZONE_INTERIOR, ZF_SEASONAL },
  { ZONE_INTERIOR, ZF_SEASONAL },
  { ZONE_SIGNAGE, ZF_EXTERIOR },
};

const BuildingDef FRENCH_BISTRO_DEF = {
  "FRENCH_BISTRO",
  5,
  FRENCH_BISTRO_LEDS
};
