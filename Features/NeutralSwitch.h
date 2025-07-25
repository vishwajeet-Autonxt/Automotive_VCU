/*
 * NeutralSwitch.h
 *
 *  Created on: 23-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef NEUTRALSWITCH_H_
#define NEUTRALSWITCH_H_
#include <stdbool.h>

// Configure GPIO pin and direction
void NeutralSwitch_Init(void);

// Read switch state (true = Neutral/SAFE, false = Not in Neutral/UNSAFE)
bool NeutralSwitch_IsActive(void);

#endif /* NEUTRALSWITCH_H_ */
