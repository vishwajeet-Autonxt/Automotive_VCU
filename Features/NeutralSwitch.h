/*
 * NeutralSwitch.h
 *
 *  Created on: 23-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef NEUTRALSWITCH_H_
#define NEUTRALSWITCH_H_

#include <stdbool.h>

void NeutralSwitch_Init(void);
bool NeutralSwitch_IsActive(void);

/*
 * Ensures Stage 2 (Battery Discharge) is only enabled
 * when Neutral Switch confirms Neutral position
 */
bool NeutralSwitch_AllowStage2(void);

#ifdef ENABLE_NEUTRAL_CAN
void NeutralSwitch_Process(void);
#endif

#endif /* NEUTRALSWITCH_H_ */
