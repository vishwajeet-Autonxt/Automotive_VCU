/*
 * MotorDriveCtrl.c
 *
 *  Created on: 28-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */


#include "S32K144.h"
#include "MotorDriveCtrl.h"

#define MOTOR_DRIVE_PORT   PORTC
#define MOTOR_DRIVE_GPIO   PTC
#define MOTOR_DRIVE_PIN    12  // PTC12

void MotorDrive_Init(void)
{
    PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;
    MOTOR_DRIVE_PORT->PCR[MOTOR_DRIVE_PIN] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    MOTOR_DRIVE_GPIO->PDDR &= ~(1 << MOTOR_DRIVE_PIN); // Input
}

bool MotorDrive_IsRequested(void)
{
    return !(MOTOR_DRIVE_GPIO->PDIR & (1 << MOTOR_DRIVE_PIN)); // Active low
}

void MotorDrive_Disable(void)
{

}

void MotorDrive_Enable(void)
{

}
