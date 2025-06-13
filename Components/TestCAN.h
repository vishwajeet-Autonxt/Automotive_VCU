/*
 * TestCAN.h
 *
 *  Created on: 11-Jun-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef TESTCAN_H_
#define TESTCAN_H_

#pragma once
#include <stdint.h>

/* ======================= PGN Definitions ======================= */
#define BATTERY_CHARGE_CONTROL_PGN 0x18FF3C11

typedef struct {
    uint8_t MR_Pos;
} PGN_18FF3C11_t;

void tx_battery_charge_control(uint8_t destAddr, const PGN_18FF3C11_t *msg);
void handle_battery_charge_control(const uint8_t *data);

#define ROLLER_FORCE_CONTROL_PGN 0x18FF3411

typedef struct {
    int16_t RollerFrcCtrl; // Roller Force Actual
    int16_t RFC_RfrcSetPt; // Roller Force SetPoint
    int16_t RFC_TiltFrcSetPt; // Tilt Force SetPoint
} PGN_18FF3411_t;

void tx_roller_force_control(uint8_t destAddr, const PGN_18FF3411_t *msg);
void handle_roller_force_control(const uint8_t *data);

#define ROLLER_POSITION_CONTROL_PGN 0x18FF3711

typedef struct {
    int16_t RollerPosCtrl; // Roller cylinder set point
    int16_t MRExt_Sol_dc; // Roller extend solenoid duty cycle
    int16_t MRRet_Sol_dc; // Roller retract solenoid duty cycle
    int16_t MR_Pos; // Roller cylinder length
} PGN_18FF3711_t;

void tx_roller_position_control(uint8_t destAddr, const PGN_18FF3711_t *msg);
void handle_roller_position_control(const uint8_t *data);

#define ROLLER_TEST_CMD_PGN 0x18FF3811

typedef struct {
    int16_t Roller_Test_Cmd; // Roller extend solenoid test duty cycle
} PGN_18FF3811_t;

void tx_roller_test_cmd(uint8_t destAddr, const PGN_18FF3811_t *msg);
void handle_roller_test_cmd(const uint8_t *data);

#define ROLLER_TEST_RES_PGN 0x18FF3911

typedef struct {
    int16_t Roller_Test_Res; // Roller retract solenoid test duty cycle
} PGN_18FF3911_t;

void tx_roller_test_res(uint8_t destAddr, const PGN_18FF3911_t *msg);
void handle_roller_test_res(const uint8_t *data);

#define WDF_TEST_CMD_PGN 0x18FF3B99

typedef struct {
    int16_t WDFTest_Cmd; // WDF pressure solenoid test duty cycle
    uint8_t WDF_Test_flag; // WDF pressure sol test command
} PGN_18FF3B99_t;

void tx_wdf_test_cmd(uint8_t destAddr, const PGN_18FF3B99_t *msg);
void handle_wdf_test_cmd(const uint8_t *data);

#define WING_DOWN_FORCE_CTRL_PGN 0x18FF3A11

typedef struct {
    int16_t WingDFCtrl; // WDF pressure set point
    int16_t WDF_PSol_dc; // WDF pressure solenoid duty cycle
    int16_t WDF_Hold; // WDF pressure valve hold
} PGN_18FF3A11_t;

void tx_wing_down_force_ctrl(uint8_t destAddr, const PGN_18FF3A11_t *msg);
void handle_wing_down_force_ctrl(const uint8_t *data);

#endif /* TESTCAN_H_ */