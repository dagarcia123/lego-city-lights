#include "building_defs.h"

/*************************
 * EXTERNAL BUILDING DEFINITIONS
 *************************/
extern const BuildingDef BUILDING_MOVIE_THEATER_DEF;

/*************************
 * BUILDING REGISTRY
 *************************/
const BuildingDef* ALL_BUILDINGS[] = {
  &BUILDING_MOVIE_THEATER_DEF
};

const uint8_t BUILDING_COUNT =
  sizeof(ALL_BUILDINGS) / sizeof(ALL_BUILDINGS[0]);

  const BuildingDef* getBuildingDefByName(const String& name) {
  for (uint8_t i = 0; i < BUILDING_COUNT; i++) {
    if (name.equalsIgnoreCase(ALL_BUILDINGS[i]->name)) {
      return ALL_BUILDINGS[i];
    }
  }
  return nullptr;
}
