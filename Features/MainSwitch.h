/*
 * MainSwitch.h
 *
 *  Created on: 21-May-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef MAINSWITCH_H_
#define MAINSWITCH_H_

#include "S32K144.h"
extern volatile uint8_t mainSwitchActive;

extern void MainSwitch_Init(void);
extern void check_main_switch_adc(void);
extern void NVIC_init_IRQs (void);
extern void LPIT0_init (void);
extern void LPIT0_Ch0_IRQHandler (void);

#endif /* MAINSWITCH_H_ */
