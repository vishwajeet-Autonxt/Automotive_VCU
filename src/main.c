#include "S32K144.h"
#include "NeutralSwitch.h"
#include "BatteryDischargeCtrl.h"

void delay_ms(volatile uint32_t ms)
{
    for (volatile uint32_t i = 0; i < ms * 4000; i++) __asm("NOP");
}

int main(void)
{
    // Initialize Neutral Switch and Battery Discharge logic
    NeutralSwitch_Init();
    BatteryDischarge_Init();

    // Configure PTD15 as output (test LED)
    PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
    PORTD->PCR[15] = PORT_PCR_MUX(1);   // PTD15 as GPIO
    PTD->PDDR |= (1 << 15);             // Output

    while (1)
    {
        // LED indicates if Neutral is active
        if (NeutralSwitch_IsActive())
        {
            PTD->PCOR = (1 << 15);   // OFF = Neutral is active
        }
        else
        {
            PTD->PSOR = (1 << 15);   // ON = Not in Neutral
        }

        // Battery Discharge logic:
        // Discharge only when ignition is in Stage2 AND neutral is active
        // For now, assume Stage2 is always active (you can later replace this with IgnitionCtrl_IsStage2Active())
        bool ignitionStage2Active = true; // Placeholder

        if (ignitionStage2Active && NeutralSwitch_IsActive())
        {
            BatteryDischarge_SetState(true);
        }
        else
        {
            BatteryDischarge_SetState(false);
        }

#ifdef ENABLE_NEUTRAL_CAN
        NeutralSwitch_Process(); // Send CAN message if enabled
#endif

        delay_ms(200);
    }
}
