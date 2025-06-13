#ifndef IGNITION_CTRL_H
#define IGNITION_CTRL_H

#include <stdbool.h>
#include <stdint.h>

// === State Definitions ===
typedef enum {
    STATE_IDLE,
    STATE_BATTERY_ON,
    STATE_MOTOR_ON,
    STATE_FAULT
} TractorState;

// === Inputs ===
typedef struct {
    bool ignition_pos1;
    bool ignition_pos2;
    bool gear_neutral;
    float battery_voltage;
    bool motor_ready;
    bool fault_detected;
} Key_Inputs;

// === Outputs ===
typedef struct {
    bool discharge_switch;      // Controls battery discharge relay
    bool motor_start_switch;    // Controls motor drive output
    TractorState current_state; // Debug or UI status
} Key_Outputs;

// === API ===
void IgnitionCtrl_Init(void);
void IgnitionCtrl_Update(const Key_Inputs* in, Key_Outputs* out);

#endif // IGNITION_CTRL_H
