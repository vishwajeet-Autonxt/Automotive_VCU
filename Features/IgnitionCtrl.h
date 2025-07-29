#ifndef IGNITION_CTRL_H
#define IGNITION_CTRL_H

#include <stdbool.h>

// Initializes GPIO for ignition key input detection
void IgnitionCtrl_Init(void);

// Checks if Stage 2 of ignition (battery discharge) is active
bool IgnitionCtrl_IsStage2Active(void);

#endif // IGNITION_CTRL_H
