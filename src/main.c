#include "sdk_project_config.h"
#include "S32K144.h"
#include "clocks_and_modes.h"
#include "PTOSwitchCtrl.h"
#include "MainSwitch.h"
#include "SteeringPositionCtrl.h"
#include "IgnitionCtrl.h"

volatile int exit_code = 0;

#define PTA ((GPIO_Type *)PTA_BASE)
#define PTB ((GPIO_Type *)PTB_BASE)
#define PTC ((GPIO_Type *)PTC_BASE)
#define PTD ((GPIO_Type *)PTD_BASE)
#define PTE ((GPIO_Type *)PTE_BASE)


/*void ADC_init(void)
{
    PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_CGC_MASK;
    ADC0->SC1[0] = ADC_SC1_ADCH(31);  // Disable module
    ADC0->CFG1 = ADC_CFG1_ADIV(3) | ADC_CFG1_MODE(1); // 12-bit
}*/

int main(void)
{
    WDOG_disable();
    SOSC_init_8MHz();
    SPLL_init_160MHz();
    NormalRUNmode_80MHz();

    PORT_init();
   // ADC_init();

    SteeringPosition_Init();
    IgnitionCtrl_Init();

    Key_Inputs in = {0};
    Key_Outputs out = {0};

    while (1)
    {
        // === Read Inputs ===
   /*     in.ignition_pos1  = (GPIO_Type->PDIR & (1 << 0)) != 0;
        in.ignition_pos2  = (GPIO_Type->PDIR & (1 << 1)) != 0;
        in.gear_neutral   = (GPIO_Type->PDIR & (1 << 2)) != 0;
        in.fault_detected = (GPIO_Type->PDIR & (1 << 3)) != 0;
        in.motor_ready    = (GPIO_Type->PDIR & (1 << 4)) != 0;*/

        in.ignition_pos1  = (PTC->PDIR & (1 << 0)) != 0;  // Read PTC0
        in.ignition_pos2  = (PTC->PDIR & (1 << 1)) != 0;  // Read PTC1
        in.gear_neutral   = (PTC->PDIR & (1 << 2)) != 0;  // Read PTC2
        in.fault_detected = (PTC->PDIR & (1 << 3)) != 0;  // Read PTC3
        in.motor_ready    = (PTC->PDIR & (1 << 4)) != 0;  // Read PTC4

        ADC0->SC1[0] = ADC_SC1_ADCH(6); // Start ADC conversion
        while ((ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0);
        uint16_t adc_val = ADC0->R[0];
        in.battery_voltage = (adc_val * 5.0f / 4095.0f) * 4.0f; // Assuming voltage divider

        // === Control Logic ===
        IgnitionCtrl_Update(&in, &out);

        // === Outputs ===
        if (out.discharge_switch)
            PTD->PSOR = (1 << 0);
        else
            PTD->PCOR = (1 << 0);

        if (out.motor_start_switch)
            PTD->PSOR = (1 << 1);
        else
            PTD->PCOR = (1 << 1);

    }

    return exit_code;
}
