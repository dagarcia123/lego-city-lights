#include <Arduino.h>

#include "config.h"
#include "wifi_manager.h"
#include "mqtt.h"
#include "ota.h"
#include "city_layout.h"
#include "led_manager.h"
#include "scene_manager.h"
#include "season_manager.h"

void setup() {
#ifdef DEBUG_SERIAL
  Serial.begin(115200);
  delay(500);
  Serial.println("\n[LegoCity] Booting...");
#endif

  // -----------------------------
  // Core services
  // -----------------------------
  initWiFi();
  initMQTT();
  initOTA();

  initScenes();
  initSeasons();

  // -----------------------------
  // Temporary city layout (TEST)
  // -----------------------------
  const char* testLayout =
    "{ \"buildings\": [ \"MOVIE_THEATER\" ] }";

  if (!setCityLayoutFromJson(testLayout)) {
#ifdef DEBUG_SERIAL
    Serial.println("[Layout] Failed to load test layout");
#endif
  }

  // -----------------------------
  // LED system
  // -----------------------------
  initLedManager(getTotalLedCount());

#ifdef DEBUG_SERIAL
  Serial.println("[LegoCity] Setup complete");
#endif
}

void loop() {
  // -----------------------------
  // Background services
  // -----------------------------
  if (wifiIsConnected()) {
    mqttLoop();
    otaLoop();
  }

  // -----------------------------
  // Scene & season logic
  // -----------------------------
  updateScenes();
  applySeason();

  // -----------------------------
  // LED rendering (THIS IS REQUIRED)
  // -----------------------------
  renderCity();

  // -----------------------------
  // Yield (non-blocking)
  // -----------------------------
  if (LOOP_DELAY_MS > 0) {
    delay(LOOP_DELAY_MS);
  }
}
