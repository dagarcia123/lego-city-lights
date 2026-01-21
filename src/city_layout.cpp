#include "city_layout.h"
#include "building_registry.h"

#include <ArduinoJson.h>


#define MAX_BUILDINGS 32

static BuildingInstance cityBuildings[MAX_BUILDINGS];
static uint16_t buildingCount = 0;
static uint16_t totalLedCount = 0;

bool setCityLayoutFromJson(const String& json) {
  buildingCount = 0;
  totalLedCount = 0;

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, json);
  if (err) {
    return false;
  }

  JsonArray arr = doc["buildings"];
  if (!arr) {
    return false;
  }

  for (JsonVariant v : arr) {
    if (buildingCount >= MAX_BUILDINGS) {
      break;
    }

    const char* id = v.as<const char*>();
    if (!id) {
      continue;
    }

    const BuildingDef* def = getBuildingDefById(id);
    if (!def) {
      continue;
    }

    cityBuildings[buildingCount].def = def;
    cityBuildings[buildingCount].led_offset = totalLedCount;

    totalLedCount += def->led_count;
    buildingCount++;
  }

  return true;
}

uint16_t getTotalLedCount() {
  return totalLedCount;
}

uint16_t getBuildingInstanceCount() {
  return buildingCount;
}

const BuildingInstance* getBuildingInstance(uint16_t index) {
  if (index >= buildingCount) return nullptr;
  return &cityBuildings[index];
}
