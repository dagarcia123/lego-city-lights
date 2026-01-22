import sys
import os
import pandas as pd

# ============================================================
# CONFIG
# ============================================================

EXCEL_FILE = "Building_Data_Model.xlsx"
SHEET_NAME = "LightingPlan"

BUILDINGS_DIR = "src/buildings"
REGISTRY_FILE = "src/building_registry.generated.cpp"

ALLOWED_ZONES = {"street", "interior", "signage", "projector"}

FLAG_COLUMNS = [
    "IsExterior",
    "IsAmbient",
    "IsSeasonal",
    "IsFeature",
]

ZONE_ENUM = {
    "street": "ZONE_STREET",
    "interior": "ZONE_INTERIOR",
    "signage": "ZONE_SIGNAGE",
    "projector": "ZONE_PROJECTOR",
}

FLAG_ENUM = {
    "IsExterior": "ZF_EXTERIOR",
    "IsAmbient": "ZF_AMBIENT",
    "IsSeasonal": "ZF_SEASONAL",
    "IsFeature": "ZF_FEATURE",
}

REQUIRED_COLUMNS = [
    "BuildingID",
    "LEDIndex",
    "Zone",
    *FLAG_COLUMNS,
]

# ============================================================
# UTILITIES
# ============================================================

def fail(msg):
    print(f"\n❌ ERROR: {msg}")
    sys.exit(1)

def normalize_bool(val):
    if pd.isna(val):
        return False
    if isinstance(val, bool):
        return val
    return str(val).strip().lower() in ("true", "1", "yes", "y")

def snake(name):
    return name.lower()

# ============================================================
# BUILDING GENERATION
# ============================================================

def generate_building_cpp(building_id, group):
    basename = snake(building_id)
    cpp_path = os.path.join(BUILDINGS_DIR, f"{basename}.cpp")

    leds = []

    for _, row in group.iterrows():
        zone = ZONE_ENUM[row["Zone"]]

        flags = [
            flag for col, flag in FLAG_ENUM.items() if row[col]
        ]

        flag_expr = " | ".join(flags) if flags else "ZF_NONE"
        leds.append((zone, flag_expr))

    led_lines = [
        f"  {{ {zone}, {flags} }},"
        for zone, flags in leds
    ]

    cpp = f"""#include "building_defs.h"

static const LedDef {building_id}_LEDS[] = {{
{os.linesep.join(led_lines)}
}};

extern const BuildingDef {building_id}_DEF = {{
  "{building_id}",
  {len(leds)},
  {building_id}_LEDS
}};
"""

    with open(cpp_path, "w", encoding="utf-8") as f:
        f.write(cpp)

    print(f"  🏗️  Generated {basename}.cpp")

# ============================================================
# REGISTRY GENERATION
# ============================================================

def generate_registry(building_ids):
    externs = [
        f"extern const BuildingDef {bid}_DEF;"
        for bid in building_ids
    ]

    entries = [
        f"  &{bid}_DEF,"
        for bid in building_ids
    ]

    cpp = f"""#include "building_registry.h"
#include <cstring>

// ----------------------------------------------------------
// GENERATED FILE — DO NOT EDIT
// Source: Building_Data_Model.xlsx
// ----------------------------------------------------------

{os.linesep.join(externs)}

static const BuildingDef* ALL_BUILDINGS[] = {{
{os.linesep.join(entries)}
}};

static const uint16_t BUILDING_COUNT =
  sizeof(ALL_BUILDINGS) / sizeof(ALL_BUILDINGS[0]);

const BuildingDef* getBuildingDefById(const char* id) {{
  if (!id) return nullptr;

  for (uint16_t i = 0; i < BUILDING_COUNT; i++) {{
    if (strcmp(ALL_BUILDINGS[i]->id, id) == 0) {{
      return ALL_BUILDINGS[i];
    }}
  }}
  return nullptr;
}}

uint16_t getBuildingCount() {{
  return BUILDING_COUNT;
}}

const BuildingDef* getBuildingByIndex(uint16_t index) {{
  if (index >= BUILDING_COUNT) return nullptr;
  return ALL_BUILDINGS[index];
}}
"""

    with open(REGISTRY_FILE, "w", encoding="utf-8") as f:
        f.write(cpp)

    print(f"\n📦 Generated building_registry.generated.cpp")

# ============================================================
# MAIN
# ============================================================

def main():
    print("🔍 Reading lighting plan...")

    try:
        df = pd.read_excel(EXCEL_FILE, sheet_name=SHEET_NAME)
    except Exception as e:
        fail(f"Failed to read Excel file: {e}")

    # Schema validation
    for col in REQUIRED_COLUMNS:
        if col not in df.columns:
            fail(f"Missing required column: {col}")

    for col in FLAG_COLUMNS:
        df[col] = df[col].apply(normalize_bool)

    if not pd.api.types.is_numeric_dtype(df["LEDIndex"]):
        fail("LEDIndex must be numeric")

    os.makedirs(BUILDINGS_DIR, exist_ok=True)

    buildings = df.groupby("BuildingID")
    building_ids = []

    print(f"\n🏙️  Generating {len(buildings)} building(s)\n")

    for building_id, group in buildings:
        group = group.sort_values("LEDIndex")
        indices = group["LEDIndex"].astype(int).tolist()

        if indices[0] != 0:
            fail(f"{building_id}: LEDIndex must start at 0")

        if indices != list(range(len(indices))):
            fail(f"{building_id}: LEDIndex must be contiguous")

        for z in group["Zone"].unique():
            if z not in ALLOWED_ZONES:
                fail(f"{building_id}: Unknown zone '{z}'")

        generate_building_cpp(building_id, group)
        building_ids.append(building_id)

    generate_registry(building_ids)

    print("\n✅ Code generation complete")

# ============================================================

if __name__ == "__main__":
    main()
