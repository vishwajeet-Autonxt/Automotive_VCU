/*
 * MainSwitch.c
 *
 *  Created on: 21-May-2025
 *      Author: Vishwajeet_Jagtap
 */
/*#include "clock.h"
#include "MainSwitch.h"
#include "PTOSwitchCtrl.h"       // Required for ADC functions (convertAdcChan, etc.)

int idle_counter = 0;
int lpit0_ch0_flag_counter = 0;
volatile uint8_t mainSwitchActive = 0;


void NVIC_init_IRQs(void) {
    S32_NVIC->ICPR[1] = 1 << (48 % 32);
    S32_NVIC->ISER[1] = 1 << (48 % 32);
    S32_NVIC->IP[48] = 0x0A;
}

void LPIT0_init(void) {
    PCC->PCCn[PCC_LPIT_INDEX] = PCC_PCCn_PCS(6);
    PCC->PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_CGC_MASK;
    LPIT0->MCR = 0x00000001;
    LPIT0->MIER = 0x00000001;
    LPIT0->TMR[0].TVAL = 80000000;  // 1s delay at 80MHz
    LPIT0->TMR[0].TCTRL = 0x00000001;
}

void check_main_switch_adc(void) {
    convertAdcChan(12);              // Potentiometer or switch ADC input
    while (adc_complete() == 0) {}   // Wait for conversion
    adcResultInMv_pot = read_adc_chx();

    if (adcResultInMv_pot > 2500) {
        mainSwitchActive = 1;
    }
}

void MainSwitch_Init(void) {
    WDOG_disable();
    PORT_init();
    SOSC_init_8MHz();
    SPLL_init_160MHz();
    NormalRUNmode_80MHz();
    ADC_init();                     // Ensure ADC is initialized

    while (!mainSwitchActive) {
        check_main_switch_adc();   // Wait until main switch is activated
    }

    NVIC_init_IRQs();
    LPIT0_init();                  // Start functionality after switch
+
    for (;;) {
        idle_counter++;
        // Add other periodic tasks here if needed
    }
}

void LPIT0_Ch0_IRQHandler(void) {
    LPIT0->MSR |= LPIT_MSR_TIF0_MASK;
    lpit0_ch0_flag_counter++;
    PTD->PTOR |= 1 << 0;           // Toggle LED for heartbeat/debug
}*/
