/*
 * CAN_Signals.h
 *
 *  Created on: 07-Oct-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef VCU_CAN_SIGNALS_H
#define VCU_CAN_SIGNALS_H

#include <stdint.h>

/* ===============================
 * VCU CAN Message Definitions
 * =============================== */

/* J1939-style CAN IDs (Extended, 29-bit) */
#define VCU_NEUTRAL_STATUS_MSG_ID   (0x18FF3411U)   /* Neutral & related signals */

/* ===============================
 * Neutral Switch Message Layout
 * PGN: 0xFF34, SA: 0x11
 * =============================== */
/* Byte0, bit assignments */
#define VCU_NEUTRAL_BIT_POS         (0U)  /* Bit0 = Neutral Switch */
#define VCU_PARK_LOCK_BIT_POS       (1U)  /* Bit1 = Park Lock (future) */
#define VCU_GEAR_POS_VALID_BIT_POS  (2U)  /* Bit2 = Gear position valid */


/* ===============================
 * Common Macros
 * =============================== */
#define SET_BIT(byte, bit)      ((byte) |= (1U << (bit)))
#define CLEAR_BIT(byte, bit)    ((byte) &= ~(1U << (bit)))
#define READ_BIT(byte, bit)     (((byte) >> (bit)) & 0x01U)

#endif /* VCU_CAN_SIGNALS_H */

