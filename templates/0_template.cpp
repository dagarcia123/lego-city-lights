#include "building_defs.h"

/******************************************************************************
 * BUILDING: <HUMAN FRIENDLY NAME>
 * ID: <mqtt_safe_name>
 *
 * PHYSICAL NOTES:
 * - Total LEDs: <auto-derived>
 * - Wiring order (LED 0 → N):
 *   1) <zone_name_1> (<count>)
 *   2) <zone_name_2> (<count>)
 *   3) <zone_name_3> (<count>)
 *
 * NOTES:
 * - Describe any quirks, extra power injection, or wiring details here
 * - Reference STL names or photo filenames if useful
 *****************************************************************************/

/*************************
 * ZONE DEFINITIONS
 * Order MUST match physical LED wiring order.
 *************************/
static const ZoneDef <BUILDING_SYMBOL>_ZONES[] = {
  { "<zone_name_1>", <count>, <ZONE_FLAGS> },
  { "<zone_name_2>", <count>, <ZONE_FLAGS> },
  { "<zone_name_3>", <count>, <ZONE_FLAGS> }
  // Add/remove zones as needed
};

/*************************
 * BUILDING DEFINITION
 *************************/
const BuildingDef <BUILDING_SYMBOL>_DEF = {
  <BUILDING_ENUM>,
  "<mqtt_safe_name>",
  LED_COUNT(<BUILDING_SYMBOL>_ZONES),
  <BUILDING_SYMBOL>_ZONES,
  ZONE_COUNT(<BUILDING_SYMBOL>_ZONES)
};
