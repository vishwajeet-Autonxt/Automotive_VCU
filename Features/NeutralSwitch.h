/*
 * NeutralSwitch.h
 *
 *  Created on: 23-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef NEUTRALSWITCH_H_
#define NEUTRALSWITCH_H_

#include <stdbool.h>

//to enable CAN transmission for neutral switch
#define ENABLE_NEUTRAL_CAN

// Configure GPIO pin and direction
void NeutralSwitch_Init(void);

// Read switch state (true = Neutral/SAFE, false = Not in Neutral/UNSAFE)
bool NeutralSwitch_IsActive(void);

// Optional CAN message function
void NeutralSwitch_Process(void);

#endif /* NEUTRALSWITCH_H_ */

