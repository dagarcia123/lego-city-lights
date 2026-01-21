#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "building_defs.h"

/************************************************************
 * CITY LAYOUT
 ************************************************************/

struct BuildingInstance {
  const BuildingDef* def;
  uint16_t led_offset;
};

bool setCityLayoutFromJson(const String& json);
uint16_t getTotalLedCount();
uint16_t getBuildingInstanceCount();
const BuildingInstance* getBuildingInstance(uint16_t index);
