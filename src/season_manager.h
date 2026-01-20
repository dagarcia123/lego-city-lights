#pragma once

#include <Arduino.h>

/*************************
 * SEASON ENUM
 *************************/
enum Season {
  SEASON_NONE,
  SEASON_HALLOWEEN,
  SEASON_CHRISTMAS,
  SEASON_WINTER,
  SEASON_SUMMER
};

/*************************
 * INIT / APPLY
 *************************/
void initSeasons();
void applySeason();

/*************************
 * SETTERS (called by MQTT)
 *************************/
bool setSeasonByName(const String& name);

/*************************
 * GETTERS
 *************************/
Season getCurrentSeason();
const char* getCurrentSeasonName();
