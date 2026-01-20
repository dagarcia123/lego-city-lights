#include "scene_manager.h"

#ifdef DEBUG_SERIAL
#include <Arduino.h>
#endif

// -----------------------------
// Internal state
// -----------------------------
static Scene currentScene = SCENE_NORMAL_NIGHT;

// -----------------------------
// Init
// -----------------------------
void initScenes() {
  currentScene = SCENE_NORMAL_NIGHT;

#ifdef DEBUG_SERIAL
  Serial.println("Scene initialized: normal_night");
#endif
}

// -----------------------------
// Update (called every loop)
// -----------------------------
void updateScenes() {
  // Placeholder for future scene-level timing logic
  // For now, scenes are purely state-based
}

// -----------------------------
// Setters
// -----------------------------
bool setSceneByName(const String& name) {
  Scene newScene;

  if (name == "normal_night") {
    newScene = SCENE_NORMAL_NIGHT;
  } else if (name == "late_night") {
    newScene = SCENE_LATE_NIGHT;
  } else if (name == "movie_time") {
    newScene = SCENE_MOVIE_TIME;
  } else if (name == "city_sleep") {
    newScene = SCENE_CITY_SLEEP;
  } else if (name == "demo") {
    newScene = SCENE_DEMO;
  } else {
#ifdef DEBUG_SERIAL
    Serial.print("Unknown scene: ");
    Serial.println(name);
#endif
    return false;
  }

  if (newScene != currentScene) {
    currentScene = newScene;

#ifdef DEBUG_SERIAL
    Serial.print("Scene changed to: ");
    Serial.println(name);
#endif
  }

  return true;
}

// -----------------------------
// Getters
// -----------------------------
Scene getCurrentScene() {
  return currentScene;
}

const char* getCurrentSceneName() {
  switch (currentScene) {
    case SCENE_NORMAL_NIGHT: return "normal_night";
    case SCENE_LATE_NIGHT:   return "late_night";
    case SCENE_MOVIE_TIME:  return "movie_time";
    case SCENE_CITY_SLEEP:  return "city_sleep";
    case SCENE_DEMO:        return "demo";
    default:                return "unknown";
  }
}
