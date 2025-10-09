/*
 * IgnitionCtrl.h
 *
 *  Created on: 25-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef IGNITIONCTRL_H_
#define IGNITIONCTRL_H_

#include <stdbool.h>

//void Ignition_Init(void);

// Stage 2 (Battery Discharge) control
//void Ignition_EnableStage2(void);
//void Ignition_DisableStage2(void);
//bool Ignition_IsStage2Enabled(void);

#include "S32K144.h"

// GPIO pin definitions
#define IGN_ON_PIN       10   // PTC10: ignition ON stage
#define START_MOM_PIN    11   // PTB11: momentary START detection
#define BLUE_LED_PIN      0   // PTD0: ON stage LED
#define RED_LED_PIN      15   // PTD15: motor/momentary LED

// Function prototypes
void Ignition_Init(void);
void Ignition_Task(void);

#endif /* IGNITIONCTRL_H_ */


