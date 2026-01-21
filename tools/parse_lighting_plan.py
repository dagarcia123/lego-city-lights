import sys
import os
import pandas as pd

# ============================================================
# CONFIG
# ============================================================

EXCEL_FILE = "Building_Data_Model.xlsx"
SHEET_NAME = "LightingPlan"
OUTPUT_DIR = "src/buildings"

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
# CODE GENERATION
# ============================================================

def generate_building_cpp(building_id, group):
    basename = snake(building_id)
    cpp_path = os.path.join(OUTPUT_DIR, f"{basename}.cpp")

    leds = []

    for _, row in group.iterrows():
        zone = ZONE_ENUM[row["Zone"]]

        flags = []
        for col, flag in FLAG_ENUM.items():
            if row[col]:
                flags.append(flag)

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

const BuildingDef {building_id}_DEF = {{
  "{building_id}",
  {len(leds)},
  {building_id}_LEDS
}};
"""

    with open(cpp_path, "w", encoding="utf-8") as f:
        f.write(cpp)

    print(f"  📝 Generated {basename}.cpp")


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

    # Normalize booleans
    for col in FLAG_COLUMNS:
        df[col] = df[col].apply(normalize_bool)

    if not pd.api.types.is_numeric_dtype(df["LEDIndex"]):
        fail("LEDIndex column must be numeric")

    os.makedirs(OUTPUT_DIR, exist_ok=True)

    buildings = df.groupby("BuildingID")

    print(f"\n🏙️  Generating {len(buildings)} building(s)\n")

    for building_id, group in buildings:
        print(f"🏠 {building_id}")

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

    print("\n✅ Building code generation complete")


if __name__ == "__main__":
    main()
