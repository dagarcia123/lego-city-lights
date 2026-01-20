#include "ota.h"
#include "config.h"

#include <WiFi.h>
#include <ArduinoOTA.h>

#ifdef DEBUG_SERIAL
#include <Arduino.h>
#endif

void initOTA() {
  ArduinoOTA.setHostname(OTA_HOSTNAME);

#ifdef OTA_PASSWORD
  ArduinoOTA.setPassword(OTA_PASSWORD);
#endif

  ArduinoOTA
    .onStart([]() {
#ifdef DEBUG_SERIAL
      Serial.println("[OTA] Update started");
#endif
    })
    .onEnd([]() {
#ifdef DEBUG_SERIAL
      Serial.println("\n[OTA] Update complete");
#endif
    })
    .onProgress([](unsigned int progress, unsigned int total) {
#ifdef DEBUG_SERIAL
      Serial.printf("[OTA] Progress: %u%%\r", (progress * 100) / total);
#endif
    })
    .onError([](ota_error_t error) {
#ifdef DEBUG_SERIAL
      Serial.printf("[OTA] Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
#endif
    });

  ArduinoOTA.begin();

#ifdef DEBUG_SERIAL
  Serial.println("[OTA] Ready");
#endif
}

void otaLoop() {
  ArduinoOTA.handle();
}
