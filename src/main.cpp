#include "wifi_manager.h"
#include "mqtt.h"
#include "ota.h"

void setup() {
  Serial.begin(115200);

  initWiFi();
  initMQTT();
  initOTA();
}

void loop() {
  mqttLoop();
  otaLoop();
}
