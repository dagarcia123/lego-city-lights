#pragma once

#include <Arduino.h>

/*************************
 * SCENE ENUM
 *************************/
enum Scene {
  SCENE_NORMAL_NIGHT,
  SCENE_LATE_NIGHT,
  SCENE_MOVIE_TIME,
  SCENE_CITY_SLEEP,
  SCENE_DEMO
};

/*************************
 * INIT / UPDATE
 *************************/
void initScenes();
void updateScenes();

/*************************
 * SETTERS (called by MQTT)
 *************************/
bool setSceneByName(const String& name);

/*************************
 * GETTERS (read-only)
 *************************/
Scene getCurrentScene();
const char* getCurrentSceneName();
