#pragma once

#include "building_defs.h"

/************************************************************
 * BUILDING REGISTRY
 * Central lookup for all building definitions
 ************************************************************/

// Returns nullptr if not found
const BuildingDef* getBuildingDefById(const char* id);

// Optional helpers
uint16_t getBuildingCount();
const BuildingDef* getBuildingByIndex(uint16_t index);
