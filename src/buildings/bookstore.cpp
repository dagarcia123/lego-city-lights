#include "building_defs.h"

static const LedDef BOOKSTORE_LEDS[] = {
  { ZONE_STREET, ZF_EXTERIOR },
  { ZONE_INTERIOR, ZF_NONE },
  { ZONE_INTERIOR, ZF_NONE },
  { ZONE_SIGNAGE, ZF_EXTERIOR },
  { ZONE_SIGNAGE, ZF_EXTERIOR },
};

extern const BuildingDef BOOKSTORE_DEF = {
  "BOOKSTORE",
  5,
  BOOKSTORE_LEDS
};
