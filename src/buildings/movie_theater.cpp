#include "building_defs.h"

/*************************
 * MOVIE THEATER
 *************************/

static const ZoneDef MOVIE_THEATER_ZONES[] = {
  { "streetlamp", 3, ZONE_EXTERIOR | ZONE_AMBIENT | ZONE_SEASONAL },
  { "interior",   6, ZONE_AMBIENT },
  { "projector",  4, ZONE_FEATURE },
  { "marquee",    6, ZONE_FEATURE | ZONE_SEASONAL }
};

const BuildingDef BUILDING_MOVIE_THEATER_DEF = {
  BUILDING_MOVIE_THEATER,
  "movie_theater",
  LED_COUNT(MOVIE_THEATER_ZONES),
  MOVIE_THEATER_ZONES,
  ZONE_COUNT(MOVIE_THEATER_ZONES)
};