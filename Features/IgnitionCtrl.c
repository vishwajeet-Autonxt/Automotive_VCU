/*
 * IgnitionCtrl.c
 *
 *  Created on: 25-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */

/*#include "S32K144.h"
#include "IgnitionCtrl.h"

#define IGNITION_STAGE2_PORT   PORTC
#define IGNITION_STAGE2_GPIO   PTC
#define IGNITION_STAGE2_PIN    13   // PTC13 as Stage 1 control relay

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
*/

/*
 * IgnitionCtrl.c
 *
 * Implementation of ignition ON/OFF control
 */

/*
 * IgnitionCtrl.c
 -----

#include "IgnitionCtrl.h"

void Ignition_Init(void)
{
    // Enable PORTC and PORTD clocks
    PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;
    PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;

    // Configure ignition input (PTC10) with pull-up (active-low detection)
    PORTC->PCR[IGN_ON_PIN] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    PTC->PDDR &= ~(1 << IGN_ON_PIN); // input

    // Configure LED output (PTD0)
    PORTD->PCR[IGN_OUT_PIN] = PORT_PCR_MUX(1);
    PTD->PDDR |= (1 << IGN_OUT_PIN);

    // LED OFF initially
    PTD->PSOR = (1 << IGN_OUT_PIN);
}

void Ignition_Task(void)
{
    // Read ignition (active-low → 0 = ON, 1 = OFF)
    uint8_t ignOn = (PTC->PDIR & (1 << IGN_ON_PIN)) ? 0 : 1;

    if (ignOn)
    {
        PTD->PCOR = (1 << IGN_OUT_PIN);  // LED ON
    }
    else
    {
        PTD->PSOR = (1 << IGN_OUT_PIN);  // LED OFF
    }
}*/
#include "IgnitionCtrl.h"

void Ignition_Init(void)
{
    // Enable clocks for PORTB, PORTC, PORTD
    PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK;
    PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;
    PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;

    // Configure ignition ON input (PTC10) with pull-up
    PORTC->PCR[IGN_ON_PIN] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    PTC->PDDR &= ~(1 << IGN_ON_PIN);

    // Configure momentary START input (PTB11) with pull-up
    PORTB->PCR[START_MOM_PIN] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    PTB->PDDR &= ~(1 << START_MOM_PIN);

    // Configure LEDs as output
    PORTD->PCR[BLUE_LED_PIN] = PORT_PCR_MUX(1);
    PORTD->PCR[RED_LED_PIN]  = PORT_PCR_MUX(1);
    PTD->PDDR |= (1 << BLUE_LED_PIN) | (1 << RED_LED_PIN);

    // LEDs OFF initially
    PTD->PSOR = (1 << BLUE_LED_PIN) | (1 << RED_LED_PIN);
}

void Ignition_Task(void)
{
    // Read ignition ON stage (active-low)
    uint8_t ignOn = (PTC->PDIR & (1 << IGN_ON_PIN)) ? 0 : 1;

    // Read momentary START (active-low)
    uint8_t startMom = (PTB->PDIR & (1 << START_MOM_PIN)) ? 0 : 1;

    // Blue LED logic
    if (ignOn && !startMom) {
        // Only ON when ignition ON and START not pressed
        PTD->PCOR = (1 << BLUE_LED_PIN);
    } else {
        PTD->PSOR = (1 << BLUE_LED_PIN);
    }

    // Red LED logic
    if (ignOn && startMom) {
        // Red ON only during START press
        PTD->PCOR = (1 << RED_LED_PIN);
    } else {
        PTD->PSOR = (1 << RED_LED_PIN);
    }
}
