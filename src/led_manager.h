#pragma once

#include <stdint.h>

void initLedManager(uint16_t total_leds);
void renderCity();

// TEST MODE
void enableTestPattern(bool enable);
