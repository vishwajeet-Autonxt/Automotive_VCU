/*
 * PositionCtrl.c
 *
 *  Created on: 21-May-2025
 *      Author: Vishwajeet_Jagtap
 */

#include "SteeringPositionCtrl.h"
#include "PTOSwitchCtrl.h"          // Provides ADC_init, convertAdcChan, adc_complete, read_adc_chx
#include "clock.h"                  // Ensure clocks are initialized
#include "S32K144.h"

#define STEERING_ADC_CHANNEL 12
#define STEERING_MAX_ANGLE_DEG 110.0f
#define ADC_MAX_COUNTS 4095.0f

static uint16_t steering_raw = 0;

void SteeringPosition_Init(void)
{
    // You should have already called WDOG_disable and clock setup in main()
    ADC_init();  // If not already initialized globally
}

uint32_t SteeringPosition_GetRaw(void)
{
    convertAdcChan(STEERING_ADC_CHANNEL);
    while (!adc_complete());
    steering_raw = read_adc_chx();  // in mV if implemented that way
    return steering_raw;
}

float SteeringPosition_GetAngleDeg(void)
{
    uint16_t adc_mv = SteeringPosition_GetRaw(); // Get millivolt reading

    // 10% to 90% Vdc maps to 0–110°
    // 10% of 5V = 500 mV, 90% of 5V = 4500 mV
    const float MIN_VOLTAGE = 500.0f;
    const float MAX_VOLTAGE = 4500.0f;
    const float SCALE = STEERING_MAX_ANGLE_DEG / (MAX_VOLTAGE - MIN_VOLTAGE);

    if (adc_mv < MIN_VOLTAGE) adc_mv = MIN_VOLTAGE;
    if (adc_mv > MAX_VOLTAGE) adc_mv = MAX_VOLTAGE;

    return (adc_mv - MIN_VOLTAGE) * SCALE;
}
