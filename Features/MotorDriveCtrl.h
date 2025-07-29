/*
 * MotorDriveCtrl.h
 *
 *  Created on: 28-Jul-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef MOTORDRIVECTRL_H_
#define MOTORDRIVECTRL_H_

#include <stdbool.h>

void MotorDrive_Init(void);
bool MotorDrive_IsRequested(void);
void MotorDrive_Disable(void);
void MotorDrive_Enable(void);

#endif /* MOTORDRIVECTRL_H_ */
