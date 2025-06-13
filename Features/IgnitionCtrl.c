#include "IgnitionCtrl.h"

#define MIN_BATTERY_VOLTAGE 11.0f

static TractorState state = STATE_IDLE;

void IgnitionCtrl_Init(void)
{
    state = STATE_IDLE;
}

void IgnitionCtrl_Update(const Key_Inputs* in, Key_Outputs* out)
{
    out->discharge_switch = false;
    out->motor_start_switch = false;

    if (in->fault_detected || in->battery_voltage < MIN_BATTERY_VOLTAGE)
    {
        state = STATE_FAULT;
    }

    switch (state)
    {
        case STATE_IDLE:
            if (in->gear_neutral && in->ignition_pos1)
            {
                state = STATE_BATTERY_ON;
            }
            break;

        case STATE_BATTERY_ON:
            out->discharge_switch = true;

            if (in->gear_neutral && in->ignition_pos2 && in->motor_ready)
            {
                state = STATE_MOTOR_ON;
            }
            break;

        case STATE_MOTOR_ON:
            out->discharge_switch = true;
            out->motor_start_switch = true;

            if (!in->ignition_pos2)  // When user releases the momentary switch
            {
                state = STATE_IDLE;
            }
            break;

        case STATE_FAULT:
        default:
            out->discharge_switch = false;
            out->motor_start_switch = false;
            state = STATE_IDLE;
            break;
    }

    out->current_state = state;
}
