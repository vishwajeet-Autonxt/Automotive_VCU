/*
 * PositionCtrl.h
 *
 *  Created on: 21-May-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef STEERINGPOSITIONCTRL_H_
#define STEERINGPOSITIONCTRL_H_

#include <stdint.h>
extern void SteeringPosition_Init(void);
extern uint32_t SteeringPosition_GetRaw(void);
extern float SteeringPosition_GetAngleDeg(void);


#endif /* STEERINGPOSITIONCTRL_H_ */
