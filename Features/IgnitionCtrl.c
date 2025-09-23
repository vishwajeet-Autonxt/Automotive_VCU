/*
 * IgnitionCtrl.c
 *
 *  Created on: 25-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */

#include "S32K144.h"
#include "IgnitionCtrl.h"

#define IGNITION_STAGE2_PORT   PORTD
#define IGNITION_STAGE2_GPIO   PTD
#define IGNITION_STAGE2_PIN    13   // PTD15 as Stage 2 control relay

static bool stage2_enabled = false;

void IgnitionCtrl_Init(void)
{
    // Enable clock for PORTD
    PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;

    // Configure PTD15 as GPIO
    IGNITION_STAGE2_PORT->PCR[IGNITION_STAGE2_PIN] = PORT_PCR_MUX(1);

    // Set PTD15 as output
    IGNITION_STAGE2_GPIO->PDDR |= (1 << IGNITION_STAGE2_PIN);

    // Default: Stage 2 disabled
    Ignition_DisableStage2();
}

void Ignition_EnableStage2(void)
{
    IGNITION_STAGE2_GPIO->PSOR = (1 << IGNITION_STAGE2_PIN); // Set High
    stage2_enabled = true;
}

void Ignition_DisableStage2(void)
{
    IGNITION_STAGE2_GPIO->PCOR = (1 << IGNITION_STAGE2_PIN); // Set Low
    stage2_enabled = false;
}

bool Ignition_IsStage2Enabled(void)
{
    return stage2_enabled;
}
