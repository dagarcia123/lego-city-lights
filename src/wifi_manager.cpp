#include "wifi_manager.h"
#include "config.h"

#include <WiFi.h>   // ← NOW this resolves correctly

#ifdef DEBUG_SERIAL
#include <Arduino.h>
#endif

void initWiFi() {
#ifdef DEBUG_SERIAL
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
#endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  uint8_t retries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef DEBUG_SERIAL
    Serial.print(".");
#endif
    if (++retries > 40) {
#ifdef DEBUG_SERIAL
      Serial.println("\nWiFi connection failed");
#endif
      return;
    }
  }

#ifdef DEBUG_SERIAL
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
#endif
}

bool wifiIsConnected() {
  return WiFi.status() == WL_CONNECTED;
}
