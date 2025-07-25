/*
 * NeutralSwitch.c
 *
 *  Created on: 23-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */


#include "S32K144.h"
#include "NeutralSwitch.h"

#define NEUTRAL_SWITCH_PORT   PORTC
#define NEUTRAL_SWITCH_GPIO   PTC
#define NEUTRAL_SWITCH_PIN    13  // PTC13

void NeutralSwitch_Init(void)
{
    // Enable clock for PORTC
    PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;

    // Set PTC14 as GPIO with pull-up
    NEUTRAL_SWITCH_PORT->PCR[NEUTRAL_SWITCH_PIN] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;

    // Set as input
    NEUTRAL_SWITCH_GPIO->PDDR &= ~(1 << NEUTRAL_SWITCH_PIN);
}

bool NeutralSwitch_IsActive(void)
{
    // ACTIVE = High
    return (NEUTRAL_SWITCH_GPIO->PDIR & (1 << NEUTRAL_SWITCH_PIN)) != 0;
}
