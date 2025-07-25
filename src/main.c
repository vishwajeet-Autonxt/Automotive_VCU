
#include "S32K144.h"
#include "NeutralSwitch.h"

void delay_ms(volatile uint32_t ms)
{
    for (volatile uint32_t i = 0; i < ms * 4000; i++) __asm("NOP");
}

int main(void)
{
    // Initialize Neutral Switch logic
    NeutralSwitch_Init();

    // Configure PTD15 as output (LED for testing)
    PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
    PORTD->PCR[15] = PORT_PCR_MUX(1);   // PTD15 as GPIO
    PTD->PDDR |= (1 << 15);             // Output

    while (1)
    {
        if (NeutralSwitch_IsActive())
        {
        	PTD->PCOR = (1 << 15);   // OFF
        }
        else
        {
        	PTD->PSOR = (1 << 15);  // ON
        }

        delay_ms(200);
    }
}
