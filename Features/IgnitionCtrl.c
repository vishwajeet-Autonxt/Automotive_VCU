/*
 * IgnitionCtrl.h
 *
 *  Created on: 21-May-2025
 *      Author: Vishwajeet_Jagtap
 */
#include "IgnitionCtrl.h"
#include "S32K144.h"

#define IGNITION_STAGE2_PORT     PORTC
#define IGNITION_STAGE2_GPIO     PTC
#define IGNITION_STAGE2_PIN      0

void IgnitionCtrl_Init(void)
{
    // Enable clock for Port C
    PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;

    // Configure PTC0 as GPIO input
    IGNITION_STAGE2_PORT->PCR[IGNITION_STAGE2_PIN] = PORT_PCR_MUX(1);
    IGNITION_STAGE2_GPIO->PDDR &= ~(1 << IGNITION_STAGE2_PIN);  // Input
}

bool IgnitionCtrl_IsStage2Active(void)
{
    return ((IGNITION_STAGE2_GPIO->PDIR & (1 << IGNITION_STAGE2_PIN)) != 0);
}
