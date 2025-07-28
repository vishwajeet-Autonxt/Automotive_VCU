/*
 * BatteryDischarge.h
 *
 *  Created on: 25-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef BATTERYDISCHARGECTRL_H_
#define BATTERYDISCHARGECTRL_H_

#include <stdbool.h>

// Initializes the battery discharge GPIO output
void BatteryDischarge_Init(void);

// Enable or disable battery discharge output
void BatteryDischarge_SetState(bool enable);

// Get current battery discharge state
bool BatteryDischarge_IsEnabled(void);


#endif /* BATTERYDISCHARGECTRL_H_ */
