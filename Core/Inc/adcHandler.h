/**
 * @file adcHandler.h
 * @authors Fabio Henrique and Guilherme Henriques
 *
 * @brief Handle with GPIO
 *
 * @date 2026-11-06
 */

#ifndef ADC_HANDLER_H
#define ADC_HANDLER_H

#include "stm32f4xx_hal.h"
#include "timerHandler.h"
#include <stdlib.h>

enum {
    SINGLE_CHANNEL,
    MULTI_CHANNEL
};

enum {
    RES12BITS,
    RES10BITS,
    RES8BITS,
    RES6BITS
};

enum {
    SMP3,
    SMP15,
    SMP28,
    SMP56,
    SMP84,
    SMP112,
    SMP144,
    SMP480
};

enum {
    PA0,
    PA1,
    PA2,
    PA3,
    PA4,
    PA5,
    PA6,
    PA7,
    PB0,
    PB1,
    PC0,
    PC1,
    PC2,
    PC3,
    PC4,
    PC5,
};

void adcStart(ADC_TypeDef* ADCx, uint8_t pin[], uint8_t channelType, uint8_t resolution);

void adcStart2(uint8_t pin, uint8_t channel, uint8_t channelType, uint8_t resolution, uint8_t sampleTime);

#endif
