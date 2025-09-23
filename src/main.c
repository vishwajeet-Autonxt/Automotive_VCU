/*
 * main.c
 *
 *  Created on: 25-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */


#include "S32K144.h"
#include "NeutralSwitch.h"
#include "BatteryDischargeCtrl.h"
#include "IgnitionCtrl.h"
#include "MotorDriveCtrl.h"

void delay_ms(volatile uint32_t ms)
{
    for (volatile uint32_t i = 0; i < ms * 4000; i++) __asm("NOP");
}

int main(void)
{
    // Initialize all modules
    NeutralSwitch_Init();
    BatteryDischarge_Init();
    //IgnitionCtrl_Init();
    //MotorDrive_Init();

    // Configure PTD15 as output for Motor Drive status indication (LED)
    PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
    PORTD->PCR[15] = PORT_PCR_MUX(1);    // PTD15 as GPIO
    PTD->PDDR |= (1 << 15);              // Set as output
    PTD->PSOR |= (1 << 15);              // Turn OFF initially (Active-Low LED)

    while (1)
    {
        // Update each module input state
        //NeutralSwitch_Update();
        //BatteryDischarge_Update();
        //IgnitionCtrl_Update();
        //MotorDrive_Update();

        // Check if all conditions are met
  //      bool ignitionOn = Ignition_IsStage2Enabled();
  //      bool neutralOK = NeutralSwitch_IsActive();
        //bool batteryOK = BatteryDischarge_IsActive();
        //bool driveButtonPressed = MotorDrive_IsButtonPressed();

       /* if (ignitionOn && neutralOK ) //&& batteryOK && driveButtonPressed)
        {
            MotorDrive_Enable();
            PTD->PSOR = (1 << 15);  // Turn ON LED (PTD15)
        }
        else
        {
            MotorDrive_Disable();
            PTD->PCOR = (1 << 15);  // Turn OFF LED (PTD15)
        }*/

        if (NeutralSwitch_IsActive())
            PTD->PCOR |= (1 << 15); // LED ON
        else
            PTD->PSOR |= (1 << 15); // LED OFF

#ifdef ENABLE_CAN_SUPPORT
        NeutralSwitch_ProcessCAN();
        BatteryDischarge_ProcessCAN();
        IgnitionCtrl_ProcessCAN();
        MotorDrive_ProcessCAN();
#endif

        delay_ms(100);
    }
}
