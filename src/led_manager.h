#pragma once

#include <Arduino.h>
#include <FastLED.h>

/*************************
 * INIT / RENDER
 *************************/
void initLEDs();
void renderLEDs();

/*************************
 * GLOBAL CONTROLS
 *************************/
void setGlobalBrightness(uint8_t brightness);
void setPowerState(bool on);

/*************************
 * LED ACCESS
 *************************/
CRGB* getLEDArray();
uint16_t getLEDCount();
