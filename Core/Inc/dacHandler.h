/**
 * @file dacHandler.h
 * @authors Fabio Henrique and Guilherme Henriques
 *
 * @brief Handle with GPIO
 *
 * @date 2026-09-17
 */

#ifndef DAC_HANDLER_H
#define DAC_HANDLER_H

#include "stm32f4xx_hal.h"
#include <stdlib.h>

enum{
    PA4,
    PA5
};

enum {
    DHR8R1,
    DHR8R2,
    DHR12L1,
    DHR12L2,
    DHR12R1,
    DHR12R2,
    DHR8RD,
    DHR12LD,
    DHR12RD

};

enum {
    SIMPLE_CHANNEL,
    DUAL_CHANNEL
};

void dacStart(uint8_t pin, uint8_t bits, uint8_t channel);
void dacStart(uint8_t pin);


#endif
