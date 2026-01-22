#include "building_defs.h"

static const LedDef MOVIE_THEATER_LEDS[] = {
  { ZONE_STREET, ZF_EXTERIOR },
  { ZONE_STREET, ZF_EXTERIOR },
  { ZONE_INTERIOR, ZF_SEASONAL },
  { ZONE_PROJECTOR, ZF_AMBIENT | ZF_FEATURE },
  { ZONE_INTERIOR, ZF_NONE },
  { ZONE_SIGNAGE, ZF_EXTERIOR },
  { ZONE_SIGNAGE, ZF_EXTERIOR },
};

extern const BuildingDef MOVIE_THEATER_DEF = {
  "MOVIE_THEATER",
  7,
  MOVIE_THEATER_LEDS
};
