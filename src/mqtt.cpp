#include "mqtt.h"

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <cstring>

#include "config.h"
#include "led_manager.h"

// --------------------------------------------------
// MQTT CLIENT
// --------------------------------------------------

static WiFiClient wifiClient;
static PubSubClient mqttClient(wifiClient);

// --------------------------------------------------
// INTERNALS
// --------------------------------------------------

static void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("[MQTT] Message arrived: ");
  Serial.println(topic);

  // Optional: print payload
  if (length > 0) {
    Serial.print("[MQTT] Payload: ");
    for (unsigned int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
  }

  // ------------------------------------------------
  // TEST COMMAND
  // ------------------------------------------------
  if (strcmp(topic, "lego_city/cmd/test") == 0) {
    Serial.println("[MQTT] Enabling LED test pattern");
    enableTestPattern(true);
    return;
  }
}

// --------------------------------------------------
// CONNECT
// --------------------------------------------------

static bool mqttConnect() {
  if (mqttClient.connected()) {
    return true;
  }

  Serial.print("[MQTT] Connecting to broker... ");

  bool connected;

  if (strlen(MQTT_USERNAME) > 0) {
    connected = mqttClient.connect(
      MQTT_CLIENT_ID,
      MQTT_USERNAME,
      MQTT_PASSWORD
    );
  } else {
    connected = mqttClient.connect(MQTT_CLIENT_ID);
  }

  if (!connected) {
    Serial.print("FAILED (rc=");
    Serial.print(mqttClient.state());
    Serial.println(")");
    return false;
  }

  Serial.println("CONNECTED");

  // ------------------------------------------------
  // SUBSCRIPTIONS
  // ------------------------------------------------

  mqttClient.subscribe("lego_city/cmd/test");
  Serial.println("[MQTT] Subscribed to lego_city/cmd/test");

  return true;
}

// --------------------------------------------------
// PUBLIC API
// --------------------------------------------------

void initMQTT() {
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);
}

void mqttLoop() {
  if (!mqttClient.connected()) {
    mqttConnect();
  }
  mqttClient.loop();
}

bool mqttIsConnected() {
  return mqttClient.connected();
}
