#pragma once

#include <Arduino.h>

/******************************************************************************
 * MQTT LIFECYCLE
 *****************************************************************************/
void initMQTT();
void mqttLoop();

// Publish helpers
void mqttPublish(const char* topic, const char* payload);