#include "building_defs.h"

static const LedDef TOWN_HALL_LEDS[] = {
  { ZONE_STREET, ZF_AMBIENT | ZF_FEATURE },
  { ZONE_STREET, ZF_EXTERIOR },
  { ZONE_INTERIOR, ZF_SEASONAL },
  { ZONE_INTERIOR, ZF_AMBIENT },
  { ZONE_INTERIOR, ZF_AMBIENT },
  { ZONE_INTERIOR, ZF_SEASONAL },
  { ZONE_INTERIOR, ZF_AMBIENT },
  { ZONE_SIGNAGE, ZF_EXTERIOR | ZF_FEATURE },
};

extern const BuildingDef TOWN_HALL_DEF = {
  "TOWN_HALL",
  8,
  TOWN_HALL_LEDS
};
