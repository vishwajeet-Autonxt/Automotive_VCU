/*
 * PTOSwitchCtrl.h
 *
 *  Created on: 21-May-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef PTOSWITCHCTRL_H_
#define PTOSWITCHCTRL_H_

#include "S32k144.h"

extern void PORT_init (void);
extern void WDOG_disable (void);
void ADC_init(void);
void convertAdcChan(uint16_t channel);
uint8_t adc_complete(void);
uint32_t read_adc_chx(void);

extern volatile uint32_t adcResultInMv_pot;


extern int PTOSwitch_Init(void);



#endif /* PTOSWITCHCTRL_H_ */
