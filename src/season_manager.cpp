#include "season_manager.h"

#include <Arduino.h>

// -----------------------------
// Internal state
// -----------------------------
static Season currentSeason = SEASON_NONE;

// -----------------------------
// Init
// -----------------------------
void initSeasons() {
  currentSeason = SEASON_NONE;

#ifdef DEBUG_SERIAL
  Serial.println("Season initialized: none");
#endif
}

// -----------------------------
// Apply (called every loop)
// -----------------------------
void applySeason() {
  // This is intentionally light-weight.
  // LED code will query getCurrentSeason()
  // and select palettes accordingly.
}

// -----------------------------
// Setters
// -----------------------------
bool setSeasonByName(const String& name) {
  Season newSeason;

  if (name == "none") {
    newSeason = SEASON_NONE;
  } else if (name == "halloween") {
    newSeason = SEASON_HALLOWEEN;
  } else if (name == "christmas") {
    newSeason = SEASON_CHRISTMAS;
  } else if (name == "winter") {
    newSeason = SEASON_WINTER;
  } else if (name == "summer") {
    newSeason = SEASON_SUMMER;
  } else {
#ifdef DEBUG_SERIAL
    Serial.print("Unknown season: ");
    Serial.println(name);
#endif
    return false;
  }

  if (newSeason != currentSeason) {
    currentSeason = newSeason;

#ifdef DEBUG_SERIAL
    Serial.print("Season changed to: ");
    Serial.println(name);
#endif
  }

  return true;
}

// -----------------------------
// Getters
// -----------------------------
Season getCurrentSeason() {
  return currentSeason;
}

const char* getCurrentSeasonName() {
  switch (currentSeason) {
    case SEASON_NONE:       return "none";
    case SEASON_HALLOWEEN:  return "halloween";
    case SEASON_CHRISTMAS:  return "christmas";
    case SEASON_WINTER:     return "winter";
    case SEASON_SUMMER:     return "summer";
    default:                return "unknown";
  }
}
