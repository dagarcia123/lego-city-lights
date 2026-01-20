#pragma once

#include <Arduino.h>
#include "building_defs.h"

/*************************
 * INIT / UPDATE
 *************************/
void initCityLayout();

/*************************
 * LAYOUT SETTERS
 *************************/
bool setCityLayoutFromJson(const String& json);

/*************************
 * QUERY HELPERS
 *************************/
uint16_t getCityLedCount();
uint8_t  getBuildingInstanceCount();

/*************************
 * ITERATION
 *************************/
struct BuildingInstance {
  const BuildingDef* def;
  uint16_t baseOffset;   // absolute LED offset in global array
};

const BuildingInstance* getBuildingInstance(uint8_t index);
