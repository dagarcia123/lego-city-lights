#pragma once

/*************************
 * DEVICE IDENTIFICATION
 *************************/
#define DEVICE_NAME "lego_city_controller"

/*************************
 * OTA CONFIG
 *************************/
#define OTA_HOSTNAME "lego-city-esp"
#define OTA_PASSWORD OTA_PASSWORD   // optional but recommended


/*************************
 * WIFI CONFIG
 *************************/
#define WIFI_SSID     WIFI_SSID
#define WIFI_PASSWORD WIFI_PASSWORD

/*************************
 * MQTT CONFIG
 *************************/
#define MQTT_BROKER     MQTT_IP
#define MQTT_PORT       1883
#define MQTT_CLIENT_ID  DEVICE_NAME
#define MQTT_USER     MQTT_USER
#define MQTT_PASSWORD MQTT_PASSWORD

#define MQTT_TOPIC_BASE "lego_city"

/*************************
 * LED CONFIG
 *************************/
#define LED_DATA_PIN  5        // GPIO pin connected to DATA IN
#define LED_TYPE      WS2812B
#define LED_COLOR     GRB

#define MAX_LEDS      500      // hard safety cap
#define DEFAULT_BRIGHTNESS  96 // safe starting point (out of 255)

/*************************
 * TIMING
 *************************/
#define LOOP_DELAY_MS 0        // keep non-blocking

/*************************
 * DEBUG FLAGS
 *************************/
// #define DEBUG_MQTT
// #define DEBUG_LAYOUT
// #define DEBUG_LED
