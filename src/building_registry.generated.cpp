#include "building_registry.h"
#include <cstring>

// ----------------------------------------------------------
// GENERATED FILE — DO NOT EDIT
// Source: Building_Data_Model.xlsx
// ----------------------------------------------------------

extern const BuildingDef MOVIE_THEATER_DEF;

static const BuildingDef* ALL_BUILDINGS[] = {
  &MOVIE_THEATER_DEF,
};

static const uint16_t BUILDING_COUNT =
  sizeof(ALL_BUILDINGS) / sizeof(ALL_BUILDINGS[0]);

const BuildingDef* getBuildingDefById(const char* id) {
  if (!id) return nullptr;

  for (uint16_t i = 0; i < BUILDING_COUNT; i++) {
    if (strcmp(ALL_BUILDINGS[i]->id, id) == 0) {
      return ALL_BUILDINGS[i];
    }
  }
  return nullptr;
}

uint16_t getBuildingCount() {
  return BUILDING_COUNT;
}

const BuildingDef* getBuildingByIndex(uint16_t index) {
  if (index >= BUILDING_COUNT) return nullptr;
  return ALL_BUILDINGS[index];
}
