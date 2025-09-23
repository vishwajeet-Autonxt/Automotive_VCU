/*
 * NeutralSwitch.c
 *
 *  Created on: 23-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */

#include "S32K144.h"
#include "NeutralSwitch.h"
#include "IgnitionCtrl.h"   // Added for Stage 2 control

#define NEUTRAL_SWITCH_PORT   PORTC
#define NEUTRAL_SWITCH_GPIO   PTC
#define NEUTRAL_SWITCH_PIN    12  // PTC15

void NeutralSwitch_Init(void)
{
    // Enable clock for PORTC
    PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;

    // Set PTC15 as GPIO with pull-up
    NEUTRAL_SWITCH_PORT->PCR[NEUTRAL_SWITCH_PIN] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;

    // Set as input
    NEUTRAL_SWITCH_GPIO->PDDR &= ~(1 << NEUTRAL_SWITCH_PIN);
}

bool NeutralSwitch_IsActive(void)
{
    // ACTIVE = High (Neutral position)
    return (NEUTRAL_SWITCH_GPIO->PDIR & (1 << NEUTRAL_SWITCH_PIN)) != 0;
}

/*
 * Ensures Stage 2 (Battery Discharge) is only enabled
 * if Neutral Safety Switch confirms Neutral position.
 */
/*bool NeutralSwitch_AllowStage2(void)
{
    if (NeutralSwitch_IsActive())
    {
        Ignition_EnableStage2();   // Allow battery discharge
        return true;
    }
    else
    {
        Ignition_DisableStage2();  // Block Stage 2 if not in Neutral
        return false;
    }
}*/

#ifdef ENABLE_NEUTRAL_CAN
void NeutralSwitch_Process(void)
{
    // Placeholder for CAN transmission logic
    // Example: transmit NeutralSwitch_IsActive() status
}
#endif
