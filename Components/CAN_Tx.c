/*
 * CAN_Tx.c
 *
 *  Created on: 07-Oct-2025
 *      Author: Vishwajeet_Jagtap
 */


#include "CAN_Tx.h"
#include "can_pal.h"
#include "sdk_project_config.h"
#include <interrupt_manager.h>
#include <stdint.h>
#include <stdbool.h>
#include "peripherals_can_pal1.h"

/**
 * @brief Sends a CAN message (classical or FD).
 *
 * @param msgId      CAN Identifier (11-bit or 29-bit)
 * @param isExtended 1 = Extended ID (29-bit), 0 = Standard (11-bit)
 * @param payload    Pointer to 8-byte payload buffer
 * @param dlc        Data Length Code (0–8)
 * @return status_t  CAN status (STATUS_SUCCESS on success)
 */
status_t CAN_SendMessage(uint32_t msgId, uint8_t isExtended, const uint8_t payload[8], uint8_t dlc)
{
    can_buff_config_t buffCfg =  {
        .enableFD = true,          /* Using CAN FD, backward compatible */
        .enableBRS = true,         /* Bit rate switch ON */
        .fdPadding = 0U,
        .idType = (isExtended ? CAN_MSG_ID_EXT : CAN_MSG_ID_STD),
        .isRemote = false
    };

    CAN_ConfigTxBuff(&can_pal1_instance, TX_MAILBOX, &buffCfg);

    can_message_t message = {
        .cs = 0U,
        .id = msgId,
        .length = dlc
    };

    /* Copy payload */
    for (int i = 0; i < dlc; i++)
        message.data[i] = payload[i];

    return CAN_Send(&can_pal1_instance, TX_MAILBOX, &message);
}
