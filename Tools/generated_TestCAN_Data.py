import pandas as pd
import os
from datetime import datetime

# === Project Paths ===
project_root = r"E:\VCU_Development\VehicleControlUnit\Automotive_VCU"
excel_path = os.path.join(project_root, "Docs", "TestCAN_Data.xlsx")
header_path = os.path.join(project_root, "Components", "TestCAN.h")
source_path = os.path.join(project_root, "Components", "TestCAN.c")

# === Read Excel Data ===
df = pd.read_excel(excel_path, sheet_name="TestCAN")
df["Function Name"] = df["Function Name"].fillna(method="ffill")

# === Metadata ===
date_str = datetime.now().strftime("%d-%b-%Y")
author_str = "Vishwajeet_Jagtap"

# === C Type Mapping ===
type_map = {
    "uint8": "uint8_t",
    "uint16": "uint16_t",
    "uint32": "uint32_t",
    "int8": "int8_t",
    "int16": "int16_t",
    "int32": "int32_t",
    "float": "float"
}

def map_ctype(ctype_raw):
    """Convert Excel type to valid C type"""
    ctype = ctype_raw.strip().lower()
    return type_map.get(ctype, ctype)  # fallback to original if not found

grouped = df.groupby("Function Name")

# === Header File Start ===
header_lines = [
    f"/*\n * TestCAN.h\n *\n *  Created on: {date_str}\n *      Author: {author_str}\n */\n",
    "#ifndef TESTCAN_H_",
    "#define TESTCAN_H_\n",
    "#pragma once",
    "#include <stdint.h>\n",
    "/* ======================= PGN Definitions ======================= */"
]

# === Source File Start ===
source_lines = [
    f"/*\n * TestCAN.c\n *\n *  Created on: {date_str}\n *      Author: {author_str}\n */\n",
    '#include "TestCAN.h"',
    "#include <string.h>\n",
    "extern void send_j1939_message(uint32_t pgn, uint8_t destAddr, uint8_t *data);\n"
]

# === Generate Content by Function ===
for func_name, group in grouped:
    pgn_macro = func_name.upper().replace(" ", "_") + "_PGN"
    pgn_id = group["CAN ID"].iloc[0]
    struct_name = f"PGN_{pgn_id.replace('0x', '')}_t"

    # === Header ===
    header_lines.append(f"#define {pgn_macro} {pgn_id}\n")

    header_lines.append(f"typedef struct {{")
    for _, row in group.iterrows():
        if pd.notna(row["Signal Name"]):
            signal = row["Signal Name"]
            ctype_raw = row["Type"]
            ctype = map_ctype(ctype_raw)
            comment = f" // {row['Description']}" if pd.notna(row.get("Description")) else ""
            header_lines.append(f"    {ctype} {signal};{comment}")
    header_lines.append(f"}} {struct_name};\n")

    fname = func_name.lower().replace(" ", "_")
    header_lines.append(f"void tx_{fname}(uint8_t destAddr, const {struct_name} *msg);")
    header_lines.append(f"void handle_{fname}(const uint8_t *data);\n")

    # === Source TX Function ===
    source_lines.append(f"void tx_{fname}(uint8_t destAddr, const {struct_name} *msg) {{")
    source_lines.append(f"    uint8_t data[8] = {{0}};")
    offset = 0
    for _, row in group.iterrows():
        if pd.notna(row["Signal Name"]):
            signal = row["Signal Name"]
            ctype = map_ctype(row["Type"])
            size = 2 if "16" in ctype else 4 if "32" in ctype else 1
            source_lines.append(f"    memcpy(&data[{offset}], &msg->{signal}, sizeof({ctype}));")
            offset += size
    source_lines.append(f"    send_j1939_message({pgn_macro}, destAddr, data);")
    source_lines.append("}\n")

    # === Source RX Function ===
    source_lines.append(f"void handle_{fname}(const uint8_t *data) {{")
    source_lines.append(f"    {struct_name} msg;")
    offset = 0
    for _, row in group.iterrows():
        if pd.notna(row["Signal Name"]):
            signal = row["Signal Name"]
            ctype = map_ctype(row["Type"])
            size = 2 if "16" in ctype else 4 if "32" in ctype else 1
            source_lines.append(f"    memcpy(&msg.{signal}, &data[{offset}], sizeof({ctype}));")
            offset += size
    source_lines.append("    // TODO: Use msg in your logic")
    source_lines.append("}\n")

# === Finalize Header ===
header_lines.append("#endif /* TESTCAN_H_ */")

# === Write to Files ===
with open(header_path, "w") as f:
    f.write("\n".join(header_lines))

with open(source_path, "w") as f:
    f.write("\n".join(source_lines))

print("✅ TestCAN.h and TestCAN.c generated successfully.")
