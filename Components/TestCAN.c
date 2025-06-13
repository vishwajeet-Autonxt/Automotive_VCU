/*
 * TestCAN.c
 *
 *  Created on: 11-Jun-2025
 *      Author: Vishwajeet_Jagtap
 */

#include "TestCAN.h"
#include <string.h>

extern void send_j1939_message(uint32_t pgn, uint8_t destAddr, uint8_t *data);

void tx_battery_charge_control(uint8_t destAddr, const PGN_18FF3C11_t *msg) {
    uint8_t data[8] = {0};
    memcpy(&data[0], &msg->MR_Pos, sizeof(uint8_t));
    send_j1939_message(BATTERY_CHARGE_CONTROL_PGN, destAddr, data);
}

void handle_battery_charge_control(const uint8_t *data) {
    PGN_18FF3C11_t msg;
    memcpy(&msg.MR_Pos, &data[0], sizeof(uint8_t));
    // TODO: Use msg in your logic
}

void tx_roller_force_control(uint8_t destAddr, const PGN_18FF3411_t *msg) {
    uint8_t data[8] = {0};
    memcpy(&data[0], &msg->RollerFrcCtrl, sizeof(int16_t));
    memcpy(&data[2], &msg->RFC_RfrcSetPt, sizeof(int16_t));
    memcpy(&data[4], &msg->RFC_TiltFrcSetPt, sizeof(int16_t));
    send_j1939_message(ROLLER_FORCE_CONTROL_PGN, destAddr, data);
}

void handle_roller_force_control(const uint8_t *data) {
    PGN_18FF3411_t msg;
    memcpy(&msg.RollerFrcCtrl, &data[0], sizeof(int16_t));
    memcpy(&msg.RFC_RfrcSetPt, &data[2], sizeof(int16_t));
    memcpy(&msg.RFC_TiltFrcSetPt, &data[4], sizeof(int16_t));
    // TODO: Use msg in your logic
}

void tx_roller_position_control(uint8_t destAddr, const PGN_18FF3711_t *msg) {
    uint8_t data[8] = {0};
    memcpy(&data[0], &msg->RollerPosCtrl, sizeof(int16_t));
    memcpy(&data[2], &msg->MRExt_Sol_dc, sizeof(int16_t));
    memcpy(&data[4], &msg->MRRet_Sol_dc, sizeof(int16_t));
    memcpy(&data[6], &msg->MR_Pos, sizeof(int16_t));
    send_j1939_message(ROLLER_POSITION_CONTROL_PGN, destAddr, data);
}

void handle_roller_position_control(const uint8_t *data) {
    PGN_18FF3711_t msg;
    memcpy(&msg.RollerPosCtrl, &data[0], sizeof(int16_t));
    memcpy(&msg.MRExt_Sol_dc, &data[2], sizeof(int16_t));
    memcpy(&msg.MRRet_Sol_dc, &data[4], sizeof(int16_t));
    memcpy(&msg.MR_Pos, &data[6], sizeof(int16_t));
    // TODO: Use msg in your logic
}

void tx_roller_test_cmd(uint8_t destAddr, const PGN_18FF3811_t *msg) {
    uint8_t data[8] = {0};
    memcpy(&data[0], &msg->Roller_Test_Cmd, sizeof(int16_t));
    send_j1939_message(ROLLER_TEST_CMD_PGN, destAddr, data);
}

void handle_roller_test_cmd(const uint8_t *data) {
    PGN_18FF3811_t msg;
    memcpy(&msg.Roller_Test_Cmd, &data[0], sizeof(int16_t));
    // TODO: Use msg in your logic
}

void tx_roller_test_res(uint8_t destAddr, const PGN_18FF3911_t *msg) {
    uint8_t data[8] = {0};
    memcpy(&data[0], &msg->Roller_Test_Res, sizeof(int16_t));
    send_j1939_message(ROLLER_TEST_RES_PGN, destAddr, data);
}

void handle_roller_test_res(const uint8_t *data) {
    PGN_18FF3911_t msg;
    memcpy(&msg.Roller_Test_Res, &data[0], sizeof(int16_t));
    // TODO: Use msg in your logic
}

void tx_wdf_test_cmd(uint8_t destAddr, const PGN_18FF3B99_t *msg) {
    uint8_t data[8] = {0};
    memcpy(&data[0], &msg->WDFTest_Cmd, sizeof(int16_t));
    memcpy(&data[2], &msg->WDF_Test_flag, sizeof(uint8_t));
    send_j1939_message(WDF_TEST_CMD_PGN, destAddr, data);
}

void handle_wdf_test_cmd(const uint8_t *data) {
    PGN_18FF3B99_t msg;
    memcpy(&msg.WDFTest_Cmd, &data[0], sizeof(int16_t));
    memcpy(&msg.WDF_Test_flag, &data[2], sizeof(uint8_t));
    // TODO: Use msg in your logic
}

void tx_wing_down_force_ctrl(uint8_t destAddr, const PGN_18FF3A11_t *msg) {
    uint8_t data[8] = {0};
    memcpy(&data[0], &msg->WingDFCtrl, sizeof(int16_t));
    memcpy(&data[2], &msg->WDF_PSol_dc, sizeof(int16_t));
    memcpy(&data[4], &msg->WDF_Hold, sizeof(int16_t));
    send_j1939_message(WING_DOWN_FORCE_CTRL_PGN, destAddr, data);
}

void handle_wing_down_force_ctrl(const uint8_t *data) {
    PGN_18FF3A11_t msg;
    memcpy(&msg.WingDFCtrl, &data[0], sizeof(int16_t));
    memcpy(&msg.WDF_PSol_dc, &data[2], sizeof(int16_t));
    memcpy(&msg.WDF_Hold, &data[4], sizeof(int16_t));
    // TODO: Use msg in your logic
}
