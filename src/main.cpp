#include <Arduino.h>

#include "config.h"

#include "wifi_manager.h"
#include "mqtt.h"
#include "ota.h"

#include "city_layout.h"
#include "led_manager.h"

#include "scene_manager.h"
#include "season_manager.h"

// --------------------------------------------------
// SETUP
// --------------------------------------------------

void setup() {
#ifdef DEBUG_SERIAL
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== LEGO CITY CONTROLLER BOOT ===");
#endif

  // ------------------------------------------------
  // WiFi / MQTT / OTA
  // ------------------------------------------------
  initWiFi();
  initMQTT();
  initOTA();

  // ------------------------------------------------
  // Scene / Season
  // ------------------------------------------------
  initScenes();
  initSeasons();

  // ------------------------------------------------
  // City layout (TEMP: static for now)
  // ------------------------------------------------
  const char* layoutJson = R"json(
  {
    "buildings": [
      "BOOKSTORE",
      "FIRE_STATION",
      "FRENCH_BISTRO",
      "MOVIE_THEATER",
      "TOWN_HALL"
    ]
  }
  )json";

  bool ok = setCityLayoutFromJson(String(layoutJson));

#ifdef DEBUG_SERIAL
  Serial.print("[MAIN] City layout load: ");
  Serial.println(ok ? "OK" : "FAILED");
  Serial.print("[MAIN] Total LEDs: ");
  Serial.println(getTotalLedCount());
#endif

  // ------------------------------------------------
  // LED INIT (AFTER layout!)
  // ------------------------------------------------
  initLedManager(getTotalLedCount());

#ifdef DEBUG_SERIAL
  Serial.println("=== SETUP COMPLETE ===");
#endif
}

// --------------------------------------------------
// LOOP
// --------------------------------------------------

void loop() {
  mqttLoop();
  otaLoop();

  updateScenes();
  applySeason();

  renderCity();

#if LOOP_DELAY_MS > 0
  delay(LOOP_DELAY_MS);
#endif
}
