#pragma once

#include "building_defs.h"

const BuildingDef* getBuildingDefById(const char* id);
uint16_t getBuildingCount();
const BuildingDef* getBuildingByIndex(uint16_t index);
