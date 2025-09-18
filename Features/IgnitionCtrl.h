/*
 * IgnitionCtrl.h
 *
 *  Created on: 25-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef IGNITIONCTRL_H_
#define IGNITIONCTRL_H_

#include <stdbool.h>

void Ignition_Init(void);

// Stage 2 (Battery Discharge) control
void Ignition_EnableStage2(void);
void Ignition_DisableStage2(void);
bool Ignition_IsStage2Enabled(void);

#endif /* IGNITIONCTRL_H_ */
