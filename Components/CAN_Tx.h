/*
 * CAN_Tx.h
 *
 *  Created on: 07-Oct-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef CAN_TX_H
#define CAN_TX_H

#include "sdk_project_config.h"
#include "CAN_Signals.h"


/* Use this define to specify if the application runs as master or slave */
#define MASTER
/* #define SLAVE */

/* Definition of the TX and RX message buffers depending on the bus role */
#if defined(MASTER)
    #define TX_MAILBOX  (1UL)
    #define TX_MSG_ID   (1UL)
    #define RX_MAILBOX  (0UL)
    #define RX_MSG_ID   (2UL)
#elif defined(SLAVE)
    #define TX_MAILBOX  (0UL)
    #define TX_MSG_ID   (2UL)
    #define RX_MAILBOX  (1UL)
    #define RX_MSG_ID   (1UL)
#endif

/* Common CAN Transmit API */
status_t CAN_SendMessage(uint32_t msgId, uint8_t isExtended, const uint8_t payload[8], uint8_t dlc);

#endif /* CAN_TX_H */

