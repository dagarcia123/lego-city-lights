#include "mqtt.h"
#include "config.h"
#include "wifi_manager.h"

#include <WiFi.h>
#include <PubSubClient.h>

#ifdef DEBUG_SERIAL
#include <Arduino.h>
#endif

static WiFiClient wifiClient;
static PubSubClient mqttClient(wifiClient);

static unsigned long lastReconnectAttempt = 0;

/******************************************************************************
 * INTERNALS
 *****************************************************************************/
static bool mqttReconnect() {
#ifdef DEBUG_SERIAL
  Serial.print("Attempting MQTT connection...");
#endif

  // Client ID (must be unique per device)
  const char* clientId = "lego_city_controller";

  bool connected = mqttClient.connect(
    clientId,
    MQTT_USER,
    MQTT_PASSWORD,
    "lego_city/status/online", // LWT topic
    0,                         // QoS
    true,                      // retained
    "false"                    // LWT payload
  );

  if (connected) {
#ifdef DEBUG_SERIAL
    Serial.println("connected");
#endif

    // Subscribe to all commands
    mqttClient.subscribe("lego_city/cmd/#");

    // Announce online (retained)
    mqttClient.publish("lego_city/status/online", "true", true);
    return true;
  }

#ifdef DEBUG_SERIAL
  Serial.print("failed, rc=");
  Serial.println(mqttClient.state());
#endif
  return false;
}

static void onMqttMessage(char* topic, byte* payload, unsigned int length) {
#ifdef DEBUG_SERIAL
  Serial.println("[MQTT] Message received");
  Serial.print("  Topic: ");
  Serial.println(topic);

  Serial.print("  Payload: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
#endif
}


/******************************************************************************
 * PUBLIC API
 *****************************************************************************/
void initMQTT() {
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(onMqttMessage);
}


void mqttLoop() {
  if (!wifiIsConnected()) return;

  if (!mqttClient.connected()) {
    unsigned long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      mqttReconnect();
    }
    return;
  }

  mqttClient.loop();
}

void mqttPublish(const char* topic, const char* payload) {
  if (!mqttClient.connected()) return;
  mqttClient.publish(topic, payload, true);
}
