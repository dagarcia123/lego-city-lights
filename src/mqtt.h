#pragma once

#include <stdint.h>

// --------------------------------------------------
// MQTT LIFECYCLE
// --------------------------------------------------

void initMQTT();
void mqttLoop();
bool mqttIsConnected();
