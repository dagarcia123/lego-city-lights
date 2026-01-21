#include "building_defs.h"

static const LedDef FIRE_STATION_LEDS[] = {
  { ZONE_STREET, ZF_EXTERIOR },
  { ZONE_STREET, ZF_EXTERIOR },
  { ZONE_INTERIOR, ZF_AMBIENT },
  { ZONE_INTERIOR, ZF_SEASONAL },
  { ZONE_INTERIOR, ZF_AMBIENT },
  { ZONE_INTERIOR, ZF_SEASONAL },
  { ZONE_INTERIOR, ZF_SEASONAL },
};

const BuildingDef FIRE_STATION_DEF = {
  "FIRE_STATION",
  7,
  FIRE_STATION_LEDS
};
