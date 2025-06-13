/*
 * clocks_and_modes.h
 *
 *  Created on: 21-May-2025
 *      Author: Vishwajeet_Jagtap
 */

#ifndef CLOCKS_AND_MODES_H_
#define CLOCKS_AND_MODES_H_

 #include "S32k144.h"

 extern void SOSC_init_8MHz(void);
 extern void SPLL_init_160MHz(void);
 extern  void NormalRUNmode_80MHz (void);

#endif /* CLOCKS_AND_MODES_H_ */
