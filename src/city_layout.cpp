
#include "city_layout.h"
#include "config.h"

#include <ArduinoJson.h>

#ifdef DEBUG_SERIAL
#include <Arduino.h>
#endif

/*************************
 * INTERNAL STATE
 *************************/
static BuildingInstance cityBuildings[16];   // max buildings in city
static uint8_t buildingCount = 0;
static uint16_t totalLedCount = 0;

/*************************
 * INIT
 *************************/
void initCityLayout() {
  buildingCount = 0;
  totalLedCount = 0;

#ifdef DEBUG_SERIAL
  Serial.println("City layout initialized (empty)");
#endif
}

/*************************
 * SET LAYOUT FROM JSON
 *
 * Expected payload:
 * ["modular_cafe","movie_theater"]
 *************************/
bool setCityLayoutFromJson(const String& json) {
  JsonDocument doc;

  DeserializationError err = deserializeJson(doc, json);
  if (err) {
#ifdef DEBUG_SERIAL
    Serial.print("Layout JSON parse failed: ");
    Serial.println(err.c_str());
#endif
    return false;
  }

  if (!doc.is<JsonArray>()) {
#ifdef DEBUG_SERIAL
    Serial.println("Layout JSON is not an array");
#endif
    return false;
  }

  JsonArray arr = doc.as<JsonArray>();

  buildingCount = 0;
  totalLedCount = 0;

  for (JsonVariant v : arr) {
    if (!v.is<const char*>()) continue;

    const String name = v.as<const char*>();
    const BuildingDef* def = getBuildingDefByName(name);

    if (!def) {
#ifdef DEBUG_SERIAL
      Serial.print("Unknown building in layout: ");
      Serial.println(name);
#endif
      continue;   // skip unknowns safely
    }

    if (buildingCount >= 16) {
#ifdef DEBUG_SERIAL
      Serial.println("City layout exceeds max building limit");
#endif
      break;
    }

    cityBuildings[buildingCount].def = def;
    cityBuildings[buildingCount].baseOffset = totalLedCount;

#ifdef DEBUG_SERIAL
    Serial.print("Added building ");
    Serial.print(def->name);
    Serial.print(" at offset ");
    Serial.println(totalLedCount);
#endif

    totalLedCount += def->ledCount;
    buildingCount++;
  }

  if (totalLedCount > MAX_LEDS) {
#ifdef DEBUG_SERIAL
    Serial.print("❌ Layout exceeds MAX_LEDS: ");
    Serial.println(totalLedCount);
#endif
    buildingCount = 0;
    totalLedCount = 0;
    return false;
  }

#ifdef DEBUG_SERIAL
  Serial.print("City layout applied. Total LEDs: ");
  Serial.println(totalLedCount);
#endif

  return true;
}

/*************************
 * QUERIES
 *************************/
uint16_t getCityLedCount() {
  return totalLedCount;
}

uint8_t getBuildingInstanceCount() {
  return buildingCount;
}

/*************************
 * ITERATION
 *************************/
const BuildingInstance* getBuildingInstance(uint8_t index) {
  if (index >= buildingCount) return nullptr;
  return &cityBuildings[index];
}
