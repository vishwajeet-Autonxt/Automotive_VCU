/*
 * BatteryDischarge.c
 *
 *  Created on: 25-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */

#include "S32K144.h"
#include "BatteryDischargeCtrl.h"

#define BATT_DISCHARGE_PORT   PORTD
#define BATT_DISCHARGE_GPIO   PTD
#define BATT_DISCHARGE_PIN    14  // Example: PTD14

static bool dischargeEnabled = false;

void BatteryDischarge_Init(void)
{
    // Enable clock to PORTD
    PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;

    // Configure PTD14 as GPIO output
    BATT_DISCHARGE_PORT->PCR[BATT_DISCHARGE_PIN] = PORT_PCR_MUX(1);  // MUX = GPIO
    BATT_DISCHARGE_GPIO->PDDR |= (1 << BATT_DISCHARGE_PIN);          // Set as output
    BATT_DISCHARGE_GPIO->PCOR = (1 << BATT_DISCHARGE_PIN);           // Default OFF
}

void BatteryDischarge_SetState(bool enable)
{
    if (enable)
    {
        BATT_DISCHARGE_GPIO->PSOR = (1 << BATT_DISCHARGE_PIN);  // Set pin HIGH
    }
    else
    {
        BATT_DISCHARGE_GPIO->PCOR = (1 << BATT_DISCHARGE_PIN);  // Set pin LOW
    }
    dischargeEnabled = enable;
}

bool BatteryDischarge_IsEnabled(void)
{
    return dischargeEnabled;
}

